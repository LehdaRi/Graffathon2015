#include "ShaderProgram.hpp"

#include <SFML/Graphics.hpp>
#include <GL/glew.h>


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

    ShaderObject vs("src/VS_Simple.glsl", GL_VERTEX_SHADER);
    ShaderObject fs("src/FS_Simple.glsl", GL_FRAGMENT_SHADER);
    ShaderProgram shader( { &vs, &fs } );


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

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
        }

        window.setActive();

        glUseProgram(shader.getId());
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.display();
    }

    glDeleteBuffers(1, &quadId);
    glDeleteVertexArrays(1, &vertexArrayId);

    return 0;
}
