#include "GTSSawOsc.hpp"
#include <vector>
#include <iostream>


GTSSawOsc::GTSSawOsc(int sampleRate) :
	GTSGenerator(sampleRate),
	ampInc_(0),
	val_(-1)
{
}


void GTSSawOsc::getChunk(std::vector<float>& buff) {
	for(int n = 0; n < buff.size(); n++) {
		stepEnv();
	    buff[n] = val_*vol_;
	    val_ += ampInc_;
	    if(val_ >= 1) {
	        val_ = -1;
	    }
	}
}


void GTSSawOsc::setFreq(int freq) {
	freq_ = freq;
	ampInc_ = float(2.0*freq) / sampleRate_;
}
