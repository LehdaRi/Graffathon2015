#ifndef GTSSQUAREOSC_HPP
#define GTSSQUAREOSC_HPP

#include <vector>
#include "GTSGenerator.hpp"

class GTSSquareOsc : public GTSGenerator
{
public:
	GTSSquareOsc(int sampleRate);
	virtual void getChunk(std::vector<float>& buff);
	virtual void setFreq(int freq);
	virtual void setDuty(float dutyCycle);
	virtual ~GTSSquareOsc() {}


private:
	float phase_;
	float phaseIncr_;
	float dutyCycle_;
	float midPoint_;
};


#endif