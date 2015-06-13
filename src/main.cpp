#include "Framebuffer.hpp"
#include "Metaballs.hpp"
#include "Pixelizer.hpp"

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <random>


#define PI  3.14159265359
#define WW  800
#define WH  600


GLfloat quad[] {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};


int main(void) {
    sf::Window window(sf::VideoMode(WW, WH), "GRAFFAAAAARGHGSOODAONHOMO");
    window.setActive();
    window.setFramerateLimit(30);
    glewInit();

    std::default_random_engine rnd(711517);

    Framebuffer fb(WW, WH);
    Metaballs mb(rnd, "src/VS_Metaballs.glsl", "src/FS_Metaballs.glsl");
    Pixelizer pixelizer("src/VS_Pixelizer.glsl", "src/FS_Pixelizer.glsl");

    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    GLuint quadId;
    glGenBuffers(1, &quadId);
    glBindBuffer(GL_ARRAY_BUFFER, quadId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, quadId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //  Render to texture shit


    //  Time
    double t = 0.0;
    const float ar = (float)WW/(float)WH;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
        }

        //such meta
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        mb.draw(quadId, fb, t, (float)WW/(float)WH);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        pixelizer.draw(quadId, t, ar, fb.getTextureId());
        /*glViewport(0, 0, WW, WH);
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glUseProgram(pixelizerShader.getId());

        glActiveTexture(GL_TEXTURE0); //make texture register 0 active
        glBindTexture(GL_TEXTURE_2D, pixelTexture); //bind textureB as
    	glUniform1i(glGetUniformLocation(pixelizerShader.getId(), "tex"), 0);

        glBindBuffer(GL_ARRAY_BUFFER, quadId);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, 6);*/

        window.display();

        t += 0.016666667;
    }


    glDeleteBuffers(1, &quadId);
    glDeleteVertexArrays(1, &vertexArrayId);

    return 0;
}
