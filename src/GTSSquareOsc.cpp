#include "GTSSquareOsc.hpp"
#include <vector>
#include <iostream>


GTSSquareOsc::GTSSquareOsc(int sampleRate) :
	GTSGenerator(sampleRate),
	phaseIncr_(0)
{
	setDuty(0.5);
}

void GTSSquareOsc::getChunk(std::vector<float>& buff) {
	for(int n = 0; n < buff.size(); n++) {
		phase_ += phaseIncr_;
		if(phase_ >= TWOPI)
			phase_ = 0;
		if(phase_ >= midPoint_)
			buff[n] = -1*vol_;
		else
			buff[n] = 1*vol_;
	}
}


void GTSSquareOsc::setFreq(int freq) {
	freq_ = freq;
	phaseIncr_ = (TWOPI / sampleRate_) * freq;
}


void GTSSquareOsc::setDuty(float dutyCycle) {
	dutyCycle_ = dutyCycle;
	midPoint_ = TWOPI * dutyCycle;
}
