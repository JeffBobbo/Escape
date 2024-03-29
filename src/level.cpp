#include "level.h"

Level* Level::fromName(const std::string& name)
{
  if (name == "prefabLobby")
    return Level::prefabLobby();
  if (name == "prefabTest")
    return Level::prefabTest();
  if (name == "prefabTestPusher")
    return Level::prefabTestPusher();

  if (name == "escape0")
    return Level::escape0();
  if (name == "escape1")
    return Level::escape1();
  if (name == "escape2")
    return Level::escape2();
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
  //for (auto it : phases)
    //delete it;
  delete graph;
  delete player;
}

void Level::idle()
{
  graph->idle();
  //for (auto it : phases)
    //it->idle();
  if (player)
  {
    player->idle();
    player->move();
  }
}

void Level::cleanup()
{
  graph->cleanup();
  //for (auto g : phases)
    //g->cleanup();
}

#include "gli.h"
void Level::draw()
{
  // translate by the players position, so the camera follows the player
  if (player)
    glTranslated(-player->getPosition().x, -player->getPosition().y, 0.0);
  graph->draw(); // draw everything in all phases first

  // draw everything else from the other phases
  //for (auto it : phases)
    //it->draw();

  if (player)
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
    /*
    for (auto p : phases)
    {
      for (auto it : p->foreground())
      {
        if (it->type() == Object::Type::EXIT)
          out = static_cast<Exit*>(it);
      }
    }
    */
  }
  return out;
}

bool Level::completed() const
{
  Exit* e = getExit();
  return e ? e->active() && player->aabbOverlap(e) : false;
}
