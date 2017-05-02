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
  static Level* prefabLobby();
  static Level* prefab0();
  static Level* prefab1();
  static Level* prefabTest();
  static Level* prefabTestTurret();
  static Level* fromName(const std::string& name);

  Level();
  Level(std::string n);
  ~Level();

  inline const std::string& getName() const { return name; }
  inline phase_t numPhases() const { return static_cast<phase_t>(phases.size()); }

  inline SceneGraph* getPhaseBase() const { return graph; }
  inline SceneGraph* getPhase(phase_t p) const { return static_cast<size_t>(p) >= phases.size() ? nullptr : phases[p]; }
  inline phase_t phasePlayer() const { return player ? player->phase : -1; }
  inline Player* getPlayer() const { return player; }

  Exit* getExit() const;
  void setCheckpoint(Checkpoint* const cp) { checkpoint = cp; }

  void idle();
  void draw();
  void cleanup();

  bool completed() const;

private:
  std::string name;
  SceneGraph* graph;
  // each scene graph represent a single phase
  std::vector<SceneGraph*> phases;

  // include a reference to the player, for convenience
  Player* player;
  mutable Exit* out;
  Checkpoint* checkpoint;
};


#endif
