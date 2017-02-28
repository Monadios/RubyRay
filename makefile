SOURCES := $(shell find . -name "*.cpp")

raycast:
	g++ -std=gnu++11 -I. $(SOURCES) -lSDL -o raycast
