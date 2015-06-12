#include "ShaderProgram.hpp"

#include <SFML/Graphics.hpp>
#include <GL/glew.h>


#define PI 3.14159265359


GLfloat quad[] {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};


int main(void) {
    sf::Window window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);
    glewInit();

    ShaderObject vs("src/VS_Metaballs.glsl", GL_VERTEX_SHADER);
    ShaderObject fs("src/FS_Metaballs.glsl", GL_FRAGMENT_SHADER);
    ShaderProgram shader( { &vs, &fs } );

    GLint uniformLoc_ballPos = glGetUniformLocation(shader.getId(), "ballPos");

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

    double t = 0.0;

    GLfloat metaballs[6] = {
        0.9f*cosf(PI*t),                0.9f*sinf(PI*t),
        0.4f+0.4f*cosf(PI*1.2345*t),    -0.8f*sinf(PI*2.23564*t),
        -0.9f*cosf(PI*2.0145*t),        0.9f*sinf(PI*0.76453*t)
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
        }

        window.setActive();

        glUseProgram(shader.getId());

        glUniform3fv(uniformLoc_ballPos, 9, metaballs);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.display();

        t += 0.016666667;
        metaballs[0] = 0.9f*cosf(PI*t);
        metaballs[1] = 0.9f*sinf(PI*t);
        metaballs[2] = 0.25f+0.15f*sinf(PI*t*0.23f);

        metaballs[3] = 0.4f+0.4f*cosf(PI*1.2345*t);
        metaballs[4] = -0.8f*sinf(PI*2.23564*t);
        metaballs[5] = 0.15f+0.05f*sinf(PI*t*0.09364f);

        metaballs[6] = 0.9f*sinf(PI*0.76453*t);
        metaballs[7] = 0.9f*sinf(PI*0.76453*t);
        metaballs[8] = 0.15f+0.07f*cos(PI*t*0.14323f);
    }

    glDeleteBuffers(1, &quadId);
    glDeleteVertexArrays(1, &vertexArrayId);

    return 0;
}
