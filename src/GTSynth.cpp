#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>
#include <cmath>
#include <array>
#include <stdio.h>
#include "GTSynth.hpp"
#include "GTSSquareOsc.hpp"
#include "GTSSawOsc.hpp"
#include "GTSTriOsc.hpp"
#include "GTSNoiseOsc.hpp"


GTSynth::GTSynth(int sampleRate) :
	sampleRate_(sampleRate),
	phase_(0),
	slots_(NUM_SLOTS, NULL),
	currSample_(0),
	currNote_(0),
	currOct_(0),
	lastTime_(0),
	tempo_(0),
	currStep_(0),
	selectedSong_(-1),
	currPat_(0),
	patStart_(0),
	stepLen_(0),
	stepStart_(0),
	songSize_(0)
{
	const std::array<float, 12> middleNotes = {
		261.63,
		277.18,
		293.66,
		311.13,
		329.63,
		349.23,
		369.99,
		392.0,
		415.30,
		440.0,
		466.16,
		493.88
	};
	for(int o = 0; o < 9; ++o) {
		for(int n = 0; n < 12; ++n) {
			notes_[o][n] = middleNotes[n] / std::pow(2, 4-o);
		}
	}
	setInstrument(0, new GTSSquareOsc(sampleRate));
	setInstrument(1, new GTSSawOsc(sampleRate));
	setInstrument(2, new GTSTriOsc(sampleRate));
	setInstrument(3, new GTSNoiseOsc(sampleRate));
	//static_cast<GTSSquareOsc*>(slots_[1])->setDuty(0.5);
}


int GTSynth::loadSong(int id, int tempo, std::string songFile, std::string patFile) {
	FILE* sf = fopen(songFile.c_str(), "r");
	FILE* pf = fopen(patFile.c_str(), "r");
	if(!sf || !pf) {
		return -1;
	}
	std::cout << "files open" << std::endl;
	char line[50];
	std::vector<std::vector<std::vector<Cmd>>> pats;
	int instrNo = 0;
	while(fgets(line, 50, pf)) {
		std::string linestd(line);
		std::cout << linestd << std::endl;
		if(line[0] == '#') {
			std::vector<Cmd> new_pat;
			sscanf(line, "# %d\n", &instrNo);
			if(instrNo <= pats.size()) {
				std::vector<std::vector<Cmd>> instrPats;
				pats.push_back(instrPats);
			}
			pats[instrNo].push_back(std::move(new_pat));
			std::cout << "new pat" << std::endl;
		} else if(line[0] != '/') {
			Cmd new_cmd;
			if(line[0] == '%') {
				std::cout << "envs" << std::endl;
				new_cmd.oct = -1;
				sscanf(line, "%% %f %f\n", &new_cmd.a, &new_cmd.r);
			} else if(line[0] == '!') {
				std::cout << "vol" << std::endl;
				new_cmd.oct = -2;
				sscanf(line, "! %f\n", &new_cmd.vol);
				std::cout << new_cmd.vol << std::endl;
			} else {
				std::cout << "notes" << std::endl;
				sscanf(line, "%d %d\n", &new_cmd.note, &new_cmd.oct);
			}
			pats[instrNo].back().push_back(new_cmd);
		}
	}
	std::vector<std::vector<int>> song;
	while(fgets(line, 50, sf)) {
		if(line[0] != '/') {
			std::vector<int> bar(8);
			sscanf(line, "%d %d %d %d %d %d %d %d\n",
					&bar[0], &bar[1], &bar[2], &bar[3], &bar[4], &bar[5], &bar[6], &bar[7]);
			song.push_back(std::move(bar));
		}
	}
	fclose(sf);
	fclose(pf);
	for(auto& instr : pats) {
		for(auto& pat : instr) {
			for(auto& cmd : pat) {
				std::cout << cmd.oct << std::endl;
				/*if(cmd.oct == -1) {
					std::cout << "env " << std::endl;
					std::cout << cmd.a << " " << cmd.r << std::endl;
				} else if(cmd.oct == -2) {
					std::cout << "vol " << std::endl;
					std::cout << cmd.vol << std::endl;
				} else {
					std::cout << "note " << std::endl;
					std::cout << cmd.note << std::endl;
					std::cout << cmd.oct << std::endl;
				}*/
			}
		}
	}
	for(auto& line : song) {
		std::cout << "line" << std::endl;
		for(auto& pat : line) {
			std::cout << pat << std::endl;
		}
	}
	pats_.push_back(pats);
	songs_.push_back(song);
	tempos_.push_back(tempo);
	return -1;
}


int GTSynth::selectSong(int id) {
	selectedSong_ = id;
	currSample_ = 0;
	songSize_ = renderedSongs_[id].size();
	return 0;
}


void GTSynth::renderSongs() {
	// Song
	for(int i = 0; i < songs_.size(); ++i) {
		std::vector<int16_t> new_song;
		int stepLen = 15.0 / tempos_[i] * sampleRate_;
		std::cout << tempos_[i] << " " << sampleRate_ << " " << stepLen << std::endl;
		// Song line
		for(int j = 0; j < songs_[i].size(); j++) {
			std::vector<int>& songLine = songs_[i][j];
			std::vector<int> offsets(8, 0);
			// Steps
			for(int k = 0; k < 16; k++) {
				// Slots
				std::vector<float> mix(stepLen, 0);
				for(int s = 0; s < 8; s++) {
					if(slots_[s]) {
						int currPat = songLine[s]-1;
						if(songLine[s] == 0) {
							slots_[s]->on(false);
						} else {
							if(currPat < 0) {
								currPat = 0;
							}
							Cmd step = pats_[i][s][currPat][k+offsets[s]];
							//std::cout << "off " << offsets[s] << " i " << i << " j " << j << " s " << s << " k " << k << std::endl;
							//std::cout << k+offsets[s] << std::endl;
							while(step.oct < 0) {
								//std::cout << step.oct << std::endl;
								if(step.oct == -1) {
									//std::cout << "env" << std::endl;
									slots_[s]->setEnv(step.a, step.r);
									offsets[s] += 1;
									//std::cout << "inc" << std::endl;
									step = pats_[i][s][currPat][k+offsets[s]];
								} else if(step.oct == -2) {
									//std::cout << "vol" << std::endl;
									slots_[s]->setVol(step.vol);
									offsets[s] += 1;
									//std::cout << "inc" << std::endl;
									step = pats_[i][s][currPat][k+offsets[s]];
								}
							}
							if(step.note == -1) {
								slots_[s]->on(false);
							} else if(step.note != -2) {
								//std::cout << step.oct << std::endl;
								//std::cout << "note" << std::endl;
								slots_[s]->setFreq(notes_[step.oct][step.note]);
								slots_[s]->on(true);
							}
							std::vector<float> chunk(stepLen);
							slots_[s]->getChunk(chunk);
							for(int n = 0; n < stepLen; ++n) {
								//std::cout << mix[n] << " -> ";
								mix[n] += chunk[n];
								//std::cout << mix[n] << std::endl;
								//std::cout << mix[n] << std::endl;
							}
						}
					}
				}
				std::vector<int16_t> converted(stepLen);
				for(int n = 0; n < stepLen; n++) {
					converted[n] = mix[n] * INT16_MAX;
				}
				std::copy(converted.begin(), converted.end(), std::back_inserter(new_song));
			}
			std::cout << "line_end" << std::endl;
		}
		std::cout << new_song.size() << std::endl;
		renderedSongs_.push_back(new_song);
	}
}


bool GTSynth::getChunk(std::vector<int16_t>& buff) {
	if(selectedSong_ == -1) {
		std::fill(buff.begin(), buff.end(), 0);
		return false;
	}
	for(int i = 0; i < buff.size(); ++i) {
		if(currSample_ >= songSize_) {
			for(int j = i; j < buff.size(); ++j) {
				buff[j] = 0;
				selectSong(selectedSong_);
				return false;
			}
		}
		buff[i] = renderedSongs_[selectedSong_][currSample_];
		currSample_ += 1;
	}
	return true;
}


void GTSynth::setInstrument(int slot, GTSGenerator* instr) {
	if(!slots_[slot]) {
		delete slots_[slot];
	}
	slots_[slot] = instr;
}


void GTSynth::setTempo(int tempo) {
	tempo_ = tempo;
	//patLen_ = 15 / tempo * sampleRate_;
}

GTSynth::~GTSynth() {
	delete slots_[0];
	delete slots_[1];
	delete slots_[2];
	delete slots_[3];
}
