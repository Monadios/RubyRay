SOURCES := $(shell find . -name "*.cpp")

raycast:
	g++ -std=gnu++11 -g -I. $(SOURCES) -lconfig++ -lSDL -o bin/raycast
