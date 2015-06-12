#include <string>
#include <vector>
#include <cstdint>
#include "GTSynth.hpp"


GTSynth::GTSynth(int sampleRate) :
	sampleRate_(sampleRate),
	phase_(0)
{
}


int GTSynth::loadSong(int id, std::string) {
	return -1;
}


void GTSynth::getChunk(std::vector<int16_t> buff) {
	int freq = 400;
	float dutyCycle = 0.5;
	float phaseIncr = (TWOPI / sampleRate_) * freq;
	float midPoint = TWOPI * dutyCycle;
	for (int n = 0; n < buff.size(); n++) {
		phase_ += phaseIncr;
		if (phase_ >= TWOPI)
			phase_ -= TWOPI; // or phase = 0;
		if (phase_ >= midPoint)
			buff[n] = -1*INT16_MIN;
		else
			buff[n] = 1*INT16_MAX;
	}
}
