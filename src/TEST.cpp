#include "GTSAudio.hpp"

int main() {
	int sampleRate = 44100;
	int bufferLength = 512;
	GTSynth synth(sampleRate);
	GTSAudio audioOut(synth, sampleRate, bufferLength);
	synth.loadSong(0, 240, "res/darude.sng", "res/darude.pat");
	synth.renderSongs();
	synth.selectSong(0);
	audioOut.play();
	while(audioOut.getStatus() == sf::SoundStream::Status::Playing) {
	}
}
