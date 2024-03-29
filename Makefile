EXEC:=Escape.out

include make.objects

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

all: $(MAIN) $(OBJECT) $(VISAGE) $(GUI)
	$(CXX) $(CXXFLAGS) $(MAIN) $(OBJECT) $(VISAGE) $(GUI) -o $(EXEC) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(warning Cleaning...)
	@$(RM) $(MAIN) $(OBJECT) $(VISAGE) $(GUI)

.PHONY: debug release all clean

