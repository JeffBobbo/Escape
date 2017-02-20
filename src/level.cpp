#include "level.h"

Level* Level::fromName(const std::string& name)
{
  if (name == "prefab0")
    return Level::prefab0();
  if (name == "prefab1")
    return Level::prefab1();
  if (name == "prefabTest")
    return Level::prefabTest();
  return nullptr;
}

Level::Level()
{
  name = "Unnamed Level";
  graph = new SceneGraph();
  player = nullptr;
  out = nullptr;
}
Level::Level(std::string n)
  : Level()
{
  name = n;
}

Level::~Level()
{
  for (auto it : phases)
    delete it;
  delete graph;
}

void Level::idle()
{
  graph->idle();
  for (auto it : phases)
    it->idle();
  player->idle();
  player->move();
}

#include "gli.h"
void Level::draw()
{
  graph->draw(); // draw everything in all phases first

  // draw everything else from the other phases
  for (auto it : phases)
    it->draw();

  player->draw(); // draw the player
}

Exit* Level::getExit() const
{
  if (out == nullptr)
  {
    for (auto it : graph->foreground())
    {
      if (it->type() == Object::Type::EXIT)
        out = static_cast<Exit*>(it);
    }
    for (auto p : phases)
    {
      for (auto it : p->foreground())
      {
        if (it->type() == Object::Type::EXIT)
          out = static_cast<Exit*>(it);
      }
    }
  }
  return out;
}

bool Level::completed() const
{
  Exit* e = getExit();
  return e ? (e->phase == (phase_t)(-1) || player->phase == e->phase) && player->aabbOverlap(e) : false;
}
