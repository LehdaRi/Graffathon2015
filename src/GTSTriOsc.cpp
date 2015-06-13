#include "GTSTriOsc.hpp"
#include <vector>
#include <iostream>


GTSTriOsc::GTSTriOsc(int sampleRate) :
	GTSGenerator(sampleRate),
	phaseIncr_(0)
{
}

void GTSTriOsc::getChunk(std::vector<float>& buff) {
	float val;
	for (int n = 0; n < buff.size(); ++n) {
	    val = phase_ * INVHALFPI;
	    if(val < 0) {
	        val += 1.0;
	    }
	    else {
	        val = 1.0 - val;
	    }
	    buff[n] = val*vol_;
	    phase_ += phaseIncr_;
	    if (phase_ >= PI) {
	        phase_ -= TWOPI;
	    }
	}
}


void GTSTriOsc::setFreq(int freq) {
	freq_ = freq;
	phaseIncr_ = (TWOPI / sampleRate_) * freq;
}
