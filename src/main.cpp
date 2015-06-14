#include "Framebuffer.hpp"
#include "Metaballs.hpp"
#include "Pixelizer.hpp"
#include "Life.hpp"
#include "Torus.hpp"

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <random>

#include "GTSynth.hpp"
#include "GTSAudio.hpp"


#define PI  3.14159265359
#define WW  1280
#define WH  720


#define METATIME 20.0f
#define LIFETIME 40.0f
#define KILLTIME 60.0f

GLfloat quad[] {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};


int main(void) {
    sf::Window window(sf::VideoMode(WW, WH), "Graffathon 2015 - Team dagen efter", sf::Style::Fullscreen);
    window.setActive();
    window.setFramerateLimit(50);
    glewInit();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::default_random_engine rnd(53236);

    Framebuffer fbFull(WW, WH);
    Framebuffer fb32(32, 32);
    Metaballs mb(rnd, "src/VS_Metaballs.glsl", "src/FS_Metaballs.glsl");
    Pixelizer pixelizer("src/VS_Pixelizer.glsl", "src/FS_Pixelizer.glsl");
    Life life("src/VS_Life.glsl", "src/FS_Life.glsl", "src/VS_LifeShade.glsl", "src/FS_LifeShade.glsl");
	Torus torus(6.0f, 3.0f, 14, 6);

    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    GLuint quadId;
    glGenBuffers(1, &quadId);
    glBindBuffer(GL_ARRAY_BUFFER, quadId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, quadId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    int sampleRate = 44100;
	int bufferLength = 512;
	GTSynth synth(sampleRate);
	GTSAudio audioOut(synth, sampleRate, bufferLength);
	synth.loadSong(0, 240, "res/darude.sng", "res/darude.pat");
	synth.renderSongs();
	synth.selectSong(0);
	audioOut.play();

    //  Time
    double t = 0.0;
    const float ar = (float)WW/(float)WH;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
        }

        if (t < METATIME) {
            glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            mb.draw(quadId, fbFull, t, ar);
            mb.draw(quadId, fb32, t, 1.0f);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, WW, WH);

            float imageBurn = (t-METATIME+8.0f)*0.25f;
            if (imageBurn < 0.0f) imageBurn = 0.0f;
            if (imageBurn > 1.0f) imageBurn = 1.0f;
            float pixelBurn = t-METATIME+1.0f;
            if (pixelBurn < 0.0f) pixelBurn = 0.0f;
            if (pixelBurn > 1.0f) pixelBurn = 1.0f;

            pixelizer.draw(quadId, t, ar, fbFull.getTextureId(), 32, 18, imageBurn, pixelBurn);
        }
        else if (t >= METATIME && t < LIFETIME) {
			life.drawBuffer(quadId, fb32, vertexArrayId);
            life.draw(quadId, fb32, ar);
        }
		else if (t >= LIFETIME && t < KILLTIME) {
			life.drawBuffer(quadId, fb32, vertexArrayId);
            //life.draw(quadId, fb32, ar);
			torus.draw(fb32, t);
		}
		else {
			return 0;
		}

        window.display();

        t += 0.025;
    }


    glDeleteBuffers(1, &quadId);
    glDeleteVertexArrays(1, &vertexArrayId);

    return 0;
}
