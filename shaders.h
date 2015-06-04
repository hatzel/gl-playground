#include <GL/glew.h>
#include <iostream>

class Program{
    public:
        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;

        std::string vertex_path;
        std::string fragment_path;
        char* vertex_status;
        char* fragment_status;

        Program(std::string vertex, std::string fragment);
        ~Program();

        void print_status();
        void compile();
    private:
        void load_single_source(std::string&, char*);
        void load_source();
        char* vertex_source;
        char* fragment_source;
};

