#include "scenegraph.h"

#include <utility>

#include "gli.h"


SceneGraph::SceneGraph()
{
  graph.insert(std::make_pair(Level::BACKGROUND, std::set<Object*>()));
  graph.insert(std::make_pair(Level::SCENARY, std::set<Object*>()));
  graph.insert(std::make_pair(Level::FOREGROUND, std::set<Object*>()));
  graph.insert(std::make_pair(Level::NPC, std::set<Object*>()));
  graph.insert(std::make_pair(Level::PLAYER, std::set<Object*>()));
  graph.insert(std::make_pair(Level::EFFECTS, std::set<Object*>()));
}

SceneGraph::~SceneGraph()
{
  for (auto it : graph)
  {
    for (Object* const o : it.second)
      delete o;
  }
}


void SceneGraph::insert(const SceneGraph::Level level, Object* object)
{
  if (!object)
    return;

  graph[level].insert(object);
}

bool SceneGraph::remove(Object* const object)
{
  if (!object)
    return false;

  for (auto it : graph)
  {
    for (auto* const it2 : it.second)
    {
      if (it2 == object)
      {
        delete it2;
        it.second.erase(it2);
        return true;
      }
    }
  }
  return false;
}

void SceneGraph::clear()
{
  for (auto it : graph)
  {
    for (Object* const o : it.second)
      delete o;
    it.second.clear();
  }
}

void SceneGraph::idle()
{
  for (auto it : graph)
  {
    for (Object* const o : it.second)
    {
      o->idle();
      o->move();
    }
  }
}
void SceneGraph::draw()
{
  for (auto it : graph)
  {
    for (Object* const o : it.second)
      o->draw();
  }
}