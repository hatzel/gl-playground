CC = g++
CPPFLAGS = -std=c++11 -Wall
LFLAGS = -lglut -lGLEW -lGL
OBJS = hello_glut.o shaders.o

all: $(OBJS)
	$(CC) -o hello $(OBJS) $(CFLAGS) $(LFLAGS)

clean:
	rm *.o hello

