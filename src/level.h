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

  inline SceneGraph* getGraph() const { return graph; }
  inline Player* getPlayer() const { return player; }

  Exit* getExit() const;
  void setCheckpoint(Checkpoint* const cp) { checkpoint = cp; }
  inline Checkpoint* getCheckpoint() const { return checkpoint; }
  
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
