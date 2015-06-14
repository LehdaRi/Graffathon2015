#include "GTSGenerator.hpp"


GTSGenerator::GTSGenerator(int sampleRate) :
	sampleRate_(sampleRate),
	freq_(0),
	vol_(1),
	amp_(1),
	aLen_(0),
	rLen_(0),
	aInc_(0),
	rDec_(0),
	phase_(0),
	state_(states::OFF)
{
}


void GTSGenerator::setVol(float vol) {
	amp_ = vol;
}


void GTSGenerator::setEnv(float A, float R) {
	aLen_ = A*sampleRate_;
	rLen_ = R*sampleRate_;
	aInc_ = 1/aLen_;
	rDec_ = 1/rLen_;
}


void GTSGenerator::on(bool state) {
	if(state) {
		state_ = states::TRIG;
		vol_ = 0;
	} else {
		state_ = states::REL;
	}
}


void GTSGenerator::stepEnv() {
	if(state_ == states::TRIG) {
		if(aLen_) {
			state_ = states::ATK;
			vol_ = 0;
		} else {
			state_ = states::ON;
			vol_ = amp_;
		}
	}
	if(state_ == states::ATK) {
		vol_ += aInc_;
		if(vol_ >= amp_) {
			state_ = states::ON;
			vol_ = amp_;
		}
	} else if(state_ == states::REL) {
		vol_ -= rDec_;
		if(vol_ <= 0) {
			state_ = states::OFF;
			vol_ = 0;
		}
	}
}


/*
void GTSGenerator::getChunk(std::vector<int16_t>& buff) {
}


void GTSGenerator::setFreq(int freq) {
}
*/
