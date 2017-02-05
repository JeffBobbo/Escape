EXEC:=Shifter.out

MAIN := main.o util.o scenegraph.o image.o input.o controls.o object/object.o object/player.o visage/polygon.o visage/particle.o visage/texture.o

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

