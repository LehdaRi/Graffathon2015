#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include "GTSynth.hpp"


GTSynth::GTSynth(int sampleRate) :
	sampleRate_(sampleRate),
	phase_(0)
{
}


int GTSynth::loadSong(int id, std::string) {
	return -1;
}


void GTSynth::getChunk(std::vector<int16_t>& buff) {
	int freq = 100;
	float dutyCycle = 0.5;
	float phaseIncr = (TWOPI / sampleRate_) * freq;
	//std::cout << phaseIncr << std::endl;
	float midPoint = TWOPI * dutyCycle;
	//std::cout << midPoint << std::endl;
	for (int n = 0; n < buff.size(); n++) {
		phase_ += phaseIncr;
		if (phase_ >= TWOPI)
			phase_ = 0;
		if (phase_ >= midPoint)
			buff[n] = INT16_MIN+500;
		else
			buff[n] = INT16_MAX-500;
		//std::cout << buff[n] << std::endl;
		//std::cout << phase_ << std::endl;
	}
}
