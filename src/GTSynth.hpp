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
	std::vector<float> envs;
	// A zero value means no change!
	std::vector<int> notes;
	std::vector<int> octs;
};


class GTSynth
{
public:
	GTSynth(int sampleRate);
    // Returns song length in seconds on success or -1 on failure
    int loadSong(int id, int tempo, std::string song, std::string pat);
    // Returns 0 on success or -1 on failure
    int selectSong(int id);
    // Calculate next song chunk
    void getChunk(std::vector<int16_t>& buff);
    void renderSongs();
    void setTempo(int tempo);
    GTSynth(const GTSynth&) = delete;


private:
	std::vector<std::vector<int16_t>> renderedSongs_;
	std::vector<std::vector<std::vector<int>>> songs_;
	std::vector<std::vector<std::vector<cmd>>> pats_;
	std::array<std::array<float, 12>, 9> notes_;
	void setInstrument(int slot, GTSGenerator* instr);
	std::vector<GTSGenerator*> slots_;
	std::vector<int> tempos_;
	int sampleRate_;
	float phase_;
	int32_t currSample_;
	int currNote_;
	int currOct_;
	float lastTime_;
	int tempo_;
	int currStep_;
	int32_t patStart_;
	int32_t stepStart_;
	int selectedSong_;
	int currPat_;
	int stepLen_;
};

#endif
