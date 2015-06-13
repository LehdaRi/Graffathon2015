#ifndef GTSAUDIO_HPP
#define GTSAUDIO_HPP


#include <SFML/Audio.hpp>
#include "GTSynth.hpp"


class GTSAudio : public sf::SoundStream
{
public:
    GTSAudio(GTSynth& source, int sampleRate, int timePerChunk);

private:
    virtual bool onGetData(sf::SoundStream::Chunk& samples);
    virtual void onSeek(sf::Time timeOffset);

    GTSynth& source_;
    int sampleRate_;
    int timePerChunk_;  // In milliseconds
    int samplesPerChunk_;
};


#endif
