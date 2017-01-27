#ifndef MAIN_H_INCLUDE
#define MAIN_H_INCLUDE

#include <stdint.h>
#include <vector>

#include "object.h"
#include "player.h"
#include "scenegraph.h"

const char* const title = "Shifter";

extern bool keys[255];
extern SceneGraph* graph;
class Player;
extern Player* player;

#endif
