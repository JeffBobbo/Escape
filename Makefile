EXEC:=Shifter.out

MAIN := main.o

# general compiler settings
CPPFLAGS=
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++11
LDFLAGS=-lglut -lGL

# putting this first makes it the default
all: $(MAIN)
	$(CXX) $(CXXFLAGS) $(MAIN) -o $(EXEC) $(LDFLAGS)

# compile for release, optimisations, no debug etc
release: CFLAGS+=-O3 -DNDEBUG
release: all

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(warning Cleaning...)
	@$(RM) $(MAIN)

.PHONY: all opt clean

