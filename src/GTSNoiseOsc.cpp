#include "GTSNoiseOsc.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>


GTSNoiseOsc::GTSNoiseOsc(int sampleRate) :
	GTSGenerator(sampleRate)
{
}

void GTSNoiseOsc::getChunk(std::vector<float>& buff) {
	for(int n = 0; n < buff.size(); n++) {
		stepEnv();
		float R1 = (float) rand() / (float) RAND_MAX;
		float R2 = (float) rand() / (float) RAND_MAX;
		buff[n] = (float) sqrt(-2.0f * log(R1)) * cos(2.0f * PI * R2)*vol_*70;
	}
}


void GTSNoiseOsc::setFreq(int freq) {
	freq_ = freq;
}
