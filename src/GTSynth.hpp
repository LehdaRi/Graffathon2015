#ifndef GTSYNTH_HPP
#define GTSYNTH_HPP


#include <string>
#include <vector>
#include <cstdint>
#include <vector>
#include <memory>
#include "GTSGenerator.hpp"

#define TWOPI 6.2831853071795864
#define INT16_MAX 32767
#define NUM_SLOTS 8


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
	void setInstrument(int slot, std::unique_ptr<GTSGenerator> instr);
	std::vector<std::unique_ptr<GTSGenerator>> slots_;
	int sampleRate_;
	float phase_;
};

#endif
