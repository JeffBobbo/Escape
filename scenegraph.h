#ifndef SCENEGRAPH_H_INCLUDE
#define SCENEGRAPH_H_INCLUDE

#include <map>
#include <set>

#include "object.h"

class SceneGraph
{
public:
  enum class Level
  {
    BACKGROUND = 0, // base layer
    SCENARY, // extra background layer
    FOREGROUND, // foreground objects, ideally stuff that can be moved/interacted
    NPC, // AI
    PLAYER, // we want the player on top of any AI
    EFFECTS // for particles and similar things, which should be on top of the player
  };
  SceneGraph();
  ~SceneGraph();

  void insert(const SceneGraph::Level level, Object* object);
  bool remove(Object* const object);
  void clear();
  void draw();

  inline const std::set<Object*>& foreground() const { return graph.at(Level::FOREGROUND); }

private:
  std::map<Level, std::set<Object* > > graph;
};

#endif
