#include "GTSynthAudio.hpp"
#include <iostream>


GTSynthAudio::GTSynthAudio(GTSynth& source, int sampleRate, int timePerChunk) :
    source_(source),
    sampleRate_(sampleRate),
    timePerChunk_(timePerChunk),
    samplesPerChunk_(sampleRate*timePerChunk/1000)
{
	initialize(1, sampleRate_);	
}


bool GTSynthAudio::onGetData(sf::SoundStream::Chunk& chunk) {
    std::vector<int16_t> buff(samplesPerChunk_);
    source_.getChunk(buff);
    /*for(auto val : buff) {
    	std::cout << val << std::endl;
    }*/
    chunk.sampleCount = samplesPerChunk_;
    //std::cout << samplesPerChunk_ << std::endl;
    chunk.samples = &buff[0];
    return true;
}


void GTSynthAudio::onSeek(sf::Time timeOffset) {
}