#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <cmath>
#include <vector>

#include "shaders.h"

#define W_HEIGHT 600
#define W_WIDTH 800

struct vec2{
    float x;
    float y;
};

GLuint vbo;
GLint color;
vec2* triangle;


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glutSwapBuffers();
}

void update(){
    display();
}

void keyboard_handler(unsigned char k, int x, int y){
    std::cout << k << std::endl;
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("HELLO GLUT");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard_handler);
    glutIdleFunc(update);

    glewExperimental = GL_TRUE;
    glewInit();
    triangle = new vec2[3]{{0.75f, 0.0f}, {0.0f, 0.5f}, {0.0f, -0.5f}};

    glClearColor(0, 0, 0, 0);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 3, triangle, GL_STREAM_DRAW);

    Program p{"vertex.glsl", "fragment.glsl"};

    GLint posAttrib = glGetAttribLocation(p.program, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    p.compile();
    glUseProgram(p.program);

    std::cout << glGetError();
    p.print_status();

    std::cout << glGetError();
    glutMainLoop();

    delete triangle;
    return 0;
}



