#ifndef SCENEGRAPH_H_INCLUDE
#define SCENEGRAPH_H_INCLUDE

#include <map>
#include <vector>

#include "object/object.h"

class SceneGraph
{
public:
  enum class Level
  {
    BACKGROUND = 0, // base layer
    SCENARY, // extra background layer
    FOREGROUND, // foreground objects, ideally stuff that can be moved/interacted
    NPC, // AI
    PLAYER, // we want anything player related on top of any AI
    EFFECTS // for particles and similar things, which should be on top of the player
  };
  SceneGraph();
  ~SceneGraph();

  void insert(const SceneGraph::Level level, Object* object);
  //bool remove(Object* const object);
  void clear();

  void idle();
  void draw();
  void cleanup();

  inline const std::vector<Object*>& level(const SceneGraph::Level level) const { return graph.at(level); }
  inline const std::vector<Object*>& foreground() const { return graph.at(Level::FOREGROUND); }

private:
  std::map<Level, std::vector<Object* > > graph;
};

#endif
