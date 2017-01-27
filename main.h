#ifndef MAIN_H_INCLUDE
#define MAIN_H_INCLUDE

#include <stdint.h>
#include <vector>

#include "object.h"
#include "player.h"

const char* const title = "Shifter";

extern bool keys[255];
extern std::vector<Object* > objects;
class Player;
extern Player* player;

#endif
