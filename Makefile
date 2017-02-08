EXEC:=Shifter.out

MAIN := src/main.o src/util.o src/scenegraph.o src/image.o src/input.o src/controls.o src/level.o src/level_prefabs.o src/object/object.o src/object/player.o src/visage/animatrix.o src/visage/polygon.o src/visage/particle.o src/visage/texture.o

# general compiler settings
CPPFLAGS=
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++11
LDFLAGS=-L/usr/lib/nvidia-304/ -lglut -lGL

debug: CXXFLAGS+=-O0 -ggdb
debug: all

# compile for release, optimisations, no debug etc
release: CXXFLAGS+=-O3
release: CPPFLAGS+=-DNDEBUG
release: all

all: $(MAIN)
	$(CXX) $(CXXFLAGS) $(MAIN) -o $(EXEC) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(warning Cleaning...)
	@$(RM) $(MAIN)

.PHONY: debug release all clean

