#include "shaders.h"
#include <fstream>
#include <assert.h>
#include <vector>
Program::Program (std::string vertex, std::string fragment):
    vertex_path(vertex),
    fragment_path(fragment)
{
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    fragment_source = new char[16384];
    vertex_source = new char[16384];

    program = glCreateProgram();

    fragment_status = new char[512];
    vertex_status = new char[512];
};

Program::~Program(){
    delete fragment_status;
    delete vertex_status;
    delete fragment_source;
    delete vertex_source;
}

void Program::load_single_source(std::string &path, char* dest){
    std::ifstream f(path, std::ifstream::in);
    for(int i = 0; (f.peek() != EOF) && (i < 16384); i++){
        dest[i] = f.get();
    }
}

void Program::load_source(){
    load_single_source(vertex_path, vertex_source);
    load_single_source(fragment_path, fragment_source);
}

std::string error(GLint status){
    if (status){
        return "Done";
    } else{
        return "Error";
    }
}

void Program::compile(){
    load_source();
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);

    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);

    GLint status;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    std::cout << "Vertex Shader: " << error(status) << std::endl;

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    std::cout << "Fragment Shader: " << error(status) << std::endl;

    glGetShaderInfoLog(fragment_shader, 512, NULL, fragment_status);
    glGetShaderInfoLog(vertex_shader, 512, NULL, vertex_status);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
     
        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
     
        for(auto l: infoLog)
        std::cout << l;
        //Provide the infolog in whatever manner you deem best.
        //Exit with failure.
    }
}


void Program::print_status(){
    std::cout << "Status of vertex Shader:" << std::endl;
    std::cout << vertex_status << std::endl;
    std::cout << "Status of fragment Shader:" << std::endl;
    std::cout << fragment_status << std::endl;
}
