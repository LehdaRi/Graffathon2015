#ifndef GTSTRIOSC_HPP
#define GTSTRIOSC_HPP

#include <vector>
#include "GTSGenerator.hpp"

class GTSTriOsc : public GTSGenerator
{
public:
	GTSTriOsc(int sampleRate);
	virtual void getChunk(std::vector<float>& buff);
	virtual void setFreq(int freq);
	virtual ~GTSTriOsc() {}


private:
	float phaseIncr_;
};


#endif