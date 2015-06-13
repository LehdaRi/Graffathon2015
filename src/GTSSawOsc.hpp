#ifndef GTSSAWOSC_HPP
#define GTSSAWOSC_HPP

#include <vector>
#include "GTSGenerator.hpp"

class GTSSawOsc : public GTSGenerator
{
public:
	GTSSawOsc(int sampleRate);
	virtual void getChunk(std::vector<float>& buff);
	virtual void setFreq(int freq);
	virtual ~GTSSawOsc() {}


private:
	float phase_;
	float ampIncr_;
	float val_;
};


#endif