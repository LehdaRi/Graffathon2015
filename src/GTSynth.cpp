#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>
#include <cmath>
#include <array>
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
	currStep_(0)
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
	std::vector<cmd> song(4);
	for(int i; i < 4; ++i) {
		song[i].notes = i+1 & (i+1) << 4 & (i+1) << 8 & (i+1) << 12
						& (i+1) << 16 & (i+1) << 20 & (i+1) << 24 & (i+1) << 28;
		song[0].octs = 1145324612;
	}
	songs_.push_back(song);
	//setInstrument(0, new GTSSquareOsc(sampleRate));
	setInstrument(1, new GTSSawOsc(sampleRate));
	//slots_[0]->setVol(0.4);
	slots_[1]->setVol(0.4);
	slots_[1]->setEnv(0.5, 0.5);
	tempo_ = 120;
}


int GTSynth::loadSong(int id, std::string) {
	return -1;
}


void GTSynth::getChunk(std::vector<int16_t>& buff) {
	int size = buff.size();
	std::vector<float> mixOut(size, 0);
	std::vector<float> temp(size);
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
		//slots_[0]->setFreq(notes_[currOct_][currNote_]);
		slots_[1]->on(true);
		slots_[1]->setFreq(notes_[currOct_][currNote_]);
	}
	currSample_ += size;
	//std::cout << currSample_/sampleRate_ << std::endl;
}


void GTSynth::setInstrument(int slot, GTSGenerator* instr) {
	if(!slots_[slot]) {
		delete slots_[slot];
	}
	slots_[slot] = instr;
}
