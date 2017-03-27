SOURCES := $(shell find . -name "*.cpp")

raycast:
	g++ -std=gnu++11 -g -I. $(SOURCES) -lSDL -o bin/raycast
