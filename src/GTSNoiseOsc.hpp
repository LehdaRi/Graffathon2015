#ifndef GTSnoiseOSC_HPP
#define GTSnoiseOSC_HPP

#include <vector>
#include "GTSGenerator.hpp"

class GTSNoiseOsc : public GTSGenerator
{
public:
	GTSNoiseOsc(int sampleRate);
	virtual void getChunk(std::vector<float>& buff);
	virtual void setFreq(int freq);
	virtual ~GTSNoiseOsc() {}
};


#endif
