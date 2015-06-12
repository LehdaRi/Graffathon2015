#ifndef GTSYNTHAUDIO_HPP
#define GTSYNTHAUDIO_HPP


#include <SFML/Audio.hpp>
#include "GTSynth.hpp"


class GTSynthAudio : public sf::SoundStream
{
public:
    GTSynthAudio(GTSynth& source, int sampleRate, int timePerChunk);

private:
    virtual bool onGetData(sf::SoundStream::Chunk& samples);
    virtual void onSeek(sf::Time timeOffset);

    GTSynth source_;
    int sampleRate_;
    int timePerChunk_;  // In milliseconds
    int samplesPerChunk_;
};


#endif
