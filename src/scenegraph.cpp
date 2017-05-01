#include "scenegraph.h"

#include <utility>

#include "gli.h"


SceneGraph::SceneGraph()
{
  graph.insert(std::make_pair(Level::BACKGROUND, std::vector<Object*>()));
  graph.insert(std::make_pair(Level::SCENARY, std::vector<Object*>()));
  graph.insert(std::make_pair(Level::FOREGROUND, std::vector<Object*>()));
  graph.insert(std::make_pair(Level::NPC, std::vector<Object*>()));
  graph.insert(std::make_pair(Level::PLAYER, std::vector<Object*>()));
  graph.insert(std::make_pair(Level::EFFECTS, std::vector<Object*>()));
}

SceneGraph::~SceneGraph()
{
  for (auto it : graph)
  {
    for (Object* const o : it.second)
      delete o;
  }
}


#include <iostream>
void SceneGraph::insert(const SceneGraph::Level level, Object* object)
{
  if (!object)
    return;

  graph[level].push_back(object);
}

/*
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
*/

void SceneGraph::clear()
{
  for (auto it : graph)
  {
    for (Object* const o : it.second)
      delete o;
    it.second.clear();
  }
}

//#include <iostream>
void SceneGraph::idle()
{
  for (auto it : graph)
  {
    for (Object* const o : it.second)
    {
      if (!o->dying())
      {
        o->idle();
        o->move();
      }
    }
  }
}

void SceneGraph::draw()
{
  for (auto it : graph)
  {
    for (Object* const o : it.second)
    {
      if (!o->dying())
        o->draw();
    }
  }
}

void SceneGraph::cleanup()
{
  for (auto& g : graph)
  {
    for (auto it = g.second.begin(); it != g.second.end(); )
    {
      Object* o = *it;
      if (o->dying())
      {
        delete o;
        it = g.second.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }
}
