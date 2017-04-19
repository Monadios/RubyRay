SOURCES := $(shell find . -name "*.cpp")

MKDIR_P = mkdir -p

raycast:
	g++ -std=gnu++11 -g -I. $(SOURCES) -lSDL -o bin/raycast
