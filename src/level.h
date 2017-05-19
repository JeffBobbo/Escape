#ifndef LEVEL_H_INCLUDE
#define LEVEL_H_INCLUDE

#include <string>
#include <vector>
#include <stdint.h>

#include "scenegraph.h"
#include "object/checkpoint.h"
#include "object/exit.h"
#include "object/player.h"

class Level
{
public:
  static Level* prefabLobby();
  static Level* prefabTest();
  static Level* prefabTestTurret();
  static Level* prefabTestPusher();

  static Level* escape0();
  static Level* escape1();
  static Level* escape2();
  static Level* fromName(const std::string& name);

  Level();
  Level(std::string n);
  ~Level();

  inline const std::string& getName() const { return name; }

  inline const SceneGraph* getGraph() const { return graph; }
  inline Player* getPlayer() const { return player; }

  Exit* getExit() const;
  void setCheckpoint(Checkpoint* const cp) { checkpoint = cp; }
  inline Checkpoint* getCheckpoint() const { return checkpoint; }
  void addPlayer(Player* const p)
  {
    player = p;
    Vec2D pos = p->getPosition();
    checkpoint = new Checkpoint(pos, true);
    graph->insert(SceneGraph::Level::FOREGROUND, checkpoint);
  }
  void insert(const SceneGraph::Level l, Object* o) { graph->insert(l, o); }

  void idle();
  void draw();
  void cleanup();

  bool completed() const;

private:
  std::string name;
  SceneGraph* graph;
  // each scene graph represent a single phase
  //std::vector<SceneGraph*> phases;

  Player* player;
  mutable Exit* out;
  Checkpoint* checkpoint;
};


#endif
