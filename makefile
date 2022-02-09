all: main

SOURCES = main.cpp Game.cpp
HEADERS = Game.hpp Point.hpp Map.hpp Hall.hpp Map_Hall.hpp

main: $(SOURCES) $(HEADERS)
	g++ -o main $(SOURCES) $(LDLIBS) $$(sdl2-config --cflags --libs)