#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>
#include "GTSynth.hpp"
#include "GTSSquareOsc.hpp"


GTSynth::GTSynth(int sampleRate) :
	sampleRate_(sampleRate),
	phase_(0),
	slots_(NUM_SLOTS)
{
	setInstrument(0, std::make_unique<GTSSquareOsc>(sampleRate));
}


int GTSynth::loadSong(int id, std::string) {
	return -1;
}


void GTSynth::getChunk(std::vector<int16_t>& buff) {
	slots_[0]->getChunk(buff);
}


void GTSynth::setInstrument(int slot, std::unique_ptr<GTSGenerator> instr) {
	slots_[slot] = std::move(instr);
}
