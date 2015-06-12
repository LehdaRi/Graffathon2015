#ifndef GTSYNTHAUDIO_HPP
#define GTSYNTHAUDIO_HPP


#include <SFML/Audio.hpp>


template<typename T>
class GTSynthAudio : public sf::SoundStream
{
public:
    GTSynthAudio(T& source, int sampleRate, int timePerChunk);

private:
    virtual bool onGetData(sf::SoundStream::Chunk samples);
    virtual void onSeek(sf::Time timeOffset);

    T& source_;
    int sampleRate_;
    int timePerChunk_;  // In milliseconds
    int samplesPerChunk_;
};


template<typename T>
GTSynthAudio<T>::GTSynthAudio(T& source, int sampleRate, int timePerChunk) :
    source_(source),
    sampleRate_(sampleRate),
    timePerChunk_(timePerChunk),
    samplesPerChunk_(sampleRate*timePerChunk/1000)
{
}


template<typename T>
bool GTSynthAudio<T>::onGetData(sf::SoundStream::Chunk chunk) {
    std::vector<int16_t> buff(samplesPerChunk_);
    source_->getChunk(buff);
    chunk.sampleCount = samplesPerChunk_;
    chunk.samples = &buff[0];
    return true;
}


template<typename T>
void GTSynthAudio<T>::onSeek(sf::Time timeOffset) {
}


#endif
