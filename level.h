#ifndef LEVEL_H_INCLUDE
#define LEVEL_H_INCLUDE

#include <string>
#include <vector>
#include <stdint.h>

#include "scenegraph.h"
#include "object/player.h"

class Level
{
public:
  static Level* prefabTest();

  Level();
  Level(std::string n);
  ~Level();

  inline const std::string& getName() const { return name; }
  inline int16_t numPhases() const { return phases.size(); }

  inline const SceneGraph* getPhaseBase() const { return graph; }
  inline const SceneGraph* getPhase(int16_t p) const { return phases[p]; }
  inline int16_t phasePlayer() const { return player ? player->phase : -1; }

  void idle();
  void draw();

private:
  std::string name;
  SceneGraph* graph;
  // each scene graph represent a single phase
  std::vector<SceneGraph*> phases;

  // include a reference to the player, for convenience
  Player* player;
};

#endif
