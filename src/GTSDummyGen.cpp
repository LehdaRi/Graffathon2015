#include "GTSDummyGen.hpp"
#include <vector>


GTSDummyGen::GTSDummyGen(int sampleRate) :
	GTSGenerator(sampleRate)
{
}


void GTSDummyGen::getChunk(std::vector<int16_t>& buff) {
}


void GTSDummyGen::setFreq(int freq) {
}
