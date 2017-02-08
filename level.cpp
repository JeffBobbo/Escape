#include "level.h"

Level::Level()
{
  name = "Unnamed Level";
  graph = nullptr;
  player = nullptr;
}
Level::Level(std::string n)
{
  Level();
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

void Level::draw()
{
  graph->draw(); // draw everything in all phases first

  // draw everything else from the other phases
  for (auto it : phases)
    it->draw();

  player->draw(); // draw the player
}
