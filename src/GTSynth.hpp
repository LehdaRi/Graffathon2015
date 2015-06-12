#ifndef GTSYNTH_HPP
#define GTSYNTH_HPP


#include <string>
#include <vector>
#include <cstdint>

#define TWOPI 6.2831853071795864
#define INT16_MAX 32767


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
private:
	int sampleRate_;
	float phase_;
};

#endif
