#ifndef MAIN_H_INCLUDE
#define MAIN_H_INCLUDE

#include <stdint.h>
#include <vector>

#include "object.h"
#include "player.h"

const char* const title = "Shifter";

extern uint64_t frame;
extern uint64_t elapsed;
extern uint64_t timebase;
extern uint64_t last;
extern uint64_t delta;
extern bool keys[255];
extern std::vector<Object* > objects;
class Player;
extern Player* player;

#endif
