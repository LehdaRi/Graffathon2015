#ifndef GTSDUMMYGEN_HPP
#define GTSDUMMYGEN_HPP

#include <vector>
#include <cstdint>
#include "GTSGenerator.hpp"


class GTSDummyGen : GTSGenerator
{
public:
	GTSDummyGen(int sampleRate);
	virtual void getChunk(std::vector<int16_t>& buff);
	virtual void setFreq(int freq);
	virtual ~GTSDummyGen() {}
};


#endif
