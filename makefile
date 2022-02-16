all: main

SOURCES = src/*.cpp
HEADERS = headers/*.hpp
EXE = tempest-atari

main: $(SOURCES) $(HEADERS)
	g++ -o $(EXE) $(SOURCES) $(LDLIBS) $$(sdl2-config --cflags --libs)

archive:
	tar -cvzf $(EXE).tar.gz headers src SDL makefile README.md

clean: 
	@$(RM) $(EXE) $(EXE).tar.gz