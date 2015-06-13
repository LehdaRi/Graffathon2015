#ifndef GTSYNTH_HPP
#define GTSYNTH_HPP


#include <string>
#include <vector>
#include <cstdint>
#include <vector>
#include <array>
#include <memory>
#include "GTSGenerator.hpp"

#define NUM_SLOTS 8
#define INT16_MAX 32767


struct cmd {
	uint32_t notes;
	uint32_t octs;
	int len;
};


class GTSynth
{
public:
	GTSynth(int sampleRate);
    // Returns song length in seconds on success or -1 on failure
    int loadSong(int id, std::string);
    // Returns 1 on success or -1 on failure
    int playSong(int id);
    // Calculate next song chunk
    void getChunk(std::vector<int16_t>& buff);
    GTSynth(const GTSynth&) = delete;


private:
	std::vector<std::vector<cmd>> songs_;
	std::array<std::array<float, 12>, 9> notes_;
	void setInstrument(int slot, GTSGenerator* instr);
	std::vector<GTSGenerator*> slots_;
	int sampleRate_;
	float phase_;
	uint32_t currSample_;
	int currNote_;
	int currOct_;
	float lastTime_;
	int tempo_;
	int currStep_;
};

#endif
