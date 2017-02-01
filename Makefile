EXEC:=Shifter.out

MAIN := main.o util.o scenegraph.o object/object.o object/player.o visage/polygon.o visage/particle.o visage/texture.o

# general compiler settings
CPPFLAGS=
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++11
LDFLAGS=-L/usr/lib/nvidia-319-updates -lglut -lGL

debug: CXXFLAGS+=-O0 -ggdb
debug: all

# compile for release, optimisations, no debug etc
release: CPPFLAGS+=-O3
release: CXXFLAGS+=-DNDEBUG
release: all

all: $(MAIN)
	$(CXX) $(CXXFLAGS) $(MAIN) -o $(EXEC) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(warning Cleaning...)
	@$(RM) $(MAIN)

.PHONY: all opt clean

