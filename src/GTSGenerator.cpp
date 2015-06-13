#include "GTSGenerator.hpp"


GTSGenerator::GTSGenerator(int sampleRate) :
	sampleRate_(sampleRate),
	freq_(0),
	vol_(1)
{
}


void GTSGenerator::setVol(float vol) {
	vol_ = vol;
}


/*
void GTSGenerator::getChunk(std::vector<int16_t>& buff) {
}


void GTSGenerator::setFreq(int freq) {
}
*/
