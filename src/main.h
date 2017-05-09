#ifndef MAIN_H_INCLUDE
#define MAIN_H_INCLUDE

#include <stdint.h>
#include <vector>

#include "object/object.h"
#include "gui/allgui.h"
#include "level.h"
#include "fontmanager.h"

const char* const title = "Shifter";

extern Level* level;
extern int32_t screenWidth;
extern int32_t screenHeight;
extern const double TILE_SIZE;
extern GUIWindow* root;
extern FontManager fontManager;

extern bool drawBoundingVolumes;
extern bool drawBoxes;
extern bool drawPaths;

#endif
