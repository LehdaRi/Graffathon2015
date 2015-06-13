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
	stepStart_(0)
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
	//setInstrument(0, new GTSSquareOsc(sampleRate));
	setInstrument(0, new GTSSawOsc(sampleRate));
	//slots_[0]->setVol(0.4);
	slots_[0]->setVol(0.4);
	slots_[0]->setEnv(0.5, 0.5);
}


int GTSynth::loadSong(int id, int tempo, std::string songFile, std::string patFile) {
	FILE* sf = fopen(songFile.c_str(), "r");
	FILE* pf = fopen(patFile.c_str(), "r");
	if(!sf || !pf) {
		return -1;
	}
	std::cout << "files open" << std::endl;
	char line[50];
	std::vector<std::vector<cmd>> pats;
	while(fgets(line, 50, pf)) {
		std::string linestd(line);
		std::cout << linestd << std::endl;
		if(line[0] == '#') {
			std::vector<cmd> new_pat;
			pats.push_back(std::move(new_pat));
			std::cout << "new pat" << std::endl;
		} else {
			cmd new_cmd;
			new_cmd.envs.resize(16);
			new_cmd.notes.resize(8);
			new_cmd.octs.resize(8);
			if(line[0] == '%') {
				std::cout << "envs" << std::endl;
				new_cmd.octs[0] = -1;
				sscanf(line, "%% %f %f / %f %f / %f %f / %f %f / %f %f / %f %f / %f %f / %f %f\n",
						&new_cmd.envs[0], &new_cmd.envs[1], &new_cmd.envs[2], &new_cmd.envs[3], &new_cmd.envs[4], &new_cmd.envs[5], &new_cmd.envs[6], &new_cmd.envs[7],
						&new_cmd.envs[8], &new_cmd.envs[9], &new_cmd.envs[10], &new_cmd.envs[11], &new_cmd.envs[12], &new_cmd.envs[13], &new_cmd.envs[14], &new_cmd.envs[15]);
				pats.back().push_back(new_cmd);
			} else {
				std::cout << "notes" << std::endl;
				sscanf(line, "%d %d / %d %d / %d %d / %d %d / %d %d / %d %d / %d %d / %d %d\n",
						&new_cmd.notes[0], &new_cmd.octs[0], &new_cmd.notes[1], &new_cmd.octs[1], &new_cmd.notes[2], &new_cmd.octs[2],
						&new_cmd.notes[3], &new_cmd.octs[3], &new_cmd.notes[4], &new_cmd.octs[4], &new_cmd.notes[5], &new_cmd.octs[5],
						&new_cmd.notes[6], &new_cmd.octs[6], &new_cmd.notes[7], &new_cmd.octs[7]);
				pats.back().push_back(new_cmd);
			}
		}
	}
	std::vector<std::vector<int>> song;
	while(fgets(line, 50, sf)) {
		std::vector<int> bar(8);
		sscanf(line, "%d %d %d %d %d %d %d %d\n",
				&bar[0], &bar[1], &bar[2], &bar[3], &bar[4], &bar[5], &bar[6], &bar[7]);
		song.push_back(std::move(bar));
	}
	fclose(sf);
	fclose(pf);
	for(auto& pat : pats) {
		for(auto& cmd : pat) {
			for(int i = 0; i < 8; ++i) {
				if(cmd.octs[0] == -1) {
					std::cout << "env " << std::endl;
					std::cout << cmd.envs[i] << std::endl;
				} else {
					std::cout << "note " << std::endl;
					std::cout << cmd.notes[i] << std::endl;
					std::cout << cmd.octs[i] << std::endl;
				}
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
	currStep_ = 0;
	currPat_ = 0;
	patStart_ = 0;
	return 0;
}


void GTSynth::renderSongs() {
	std::cout << "yee" << pats_[0][0][0].octs[0] << std::endl;
	// Song
	//std::cout << "1" << std::endl << std::flush;
	for(int i = 0; i < songs_.size(); ++i) {
		//std::cout << "2" << std::endl << std::flush;
		std::vector<int16_t> new_song;
		int stepLen = 15 / tempos_[i] * sampleRate_;
		// Song line
		for(int j = 0; j < songs_[i].size(); ++j) {
			//std::cout << "3" << std::endl << std::flush;
			std::vector<int>& songLine = songs_[i][j];
			// Steps
			for(int k = 0; k < 16; ++k) {
				//std::cout << "5" << std::endl << std::flush;
				// Slots
				for(int s = 0; s < 8; ++s) {
					//std::cout << "6" << std::endl << std::flush;
					if(slots_[s]) {
						cmd& step = pats_[i][songLine[s]][k];
						if(step.octs[0] == -1) {
							// säädä envit
						} else {
							std::cout << notes_[step.octs[s]][step.notes[s]] << std::endl;
							slots_[s]->setFreq(notes_[step.octs[s]][step.notes[s]]);
						}
						//std::cout << step.notes[0] << std::endl;
						//slots_[s]->setFreq(notes_[(pats_[i][songLine[s]][k].octs[s])][(notes_[pats_[i][songLine[s]][k].notes[s]-48])]);
						//slots_[s]->setFreq(notes_[pats_[i][j][k].octs[k]][pats_[i][j][k].notes[k]-48]);
					}
				}
			}
		}
	}
}


void GTSynth::getChunk(std::vector<int16_t>& buff) {
	if(selectedSong_ != -1) {
		std::fill(buff.begin(), buff.end(), 0);
		return;
	}
	std::fill(buff.begin(), buff.end(), 0);
	/*
	int outSize = buff.size();
	std::vector<float> mixOut(outSize, 0);
	std::vector<float> temp(outSize);
	for(int i = 0; i < NUM_SLOTS; ++i) {
		if(slots_[i]) {
			slots_[i]->getChunk(temp);
			for(int j = 0; j < size; ++j) {
				mixOut[j] += temp[j];
			}
		}
	}
	for(int i = 0; i < buff.size(); ++i) {
		buff[i] = mixOut[i]*INT16_MAX;
	}
	if(currSample_/sampleRate_-lastTime_ >= 0.5) {
		if(currNote_ == 11) {
			currOct_ = (currOct_ + 1) % 9;
		}
		currNote_ = (currNote_ + 1) % 12;
		slots_[1]->on(true);
		slots_[1]->setFreq(notes_[currOct_][currNote_]);
	}
	currSample_ += size;
	*/
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
