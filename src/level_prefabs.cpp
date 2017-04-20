#include "level.h"

#include "scenegraph.h"
#include "object/allobject.h"
#include "visage/allvisage.h"

#include "util.h"
#include "colour.h"

Level* Level::prefabLobby()
{
  Level* level = new Level("");
  Object* bg = new Object();
  VisageTexture* vt = new VisageTexture(50, 50, "img/background/tile0.png");
  vt->setRepeat(50.0, 50.0);
  bg->setVisage(vt);
  level->graph->insert(SceneGraph::Level::BACKGROUND, bg);
  return level;
}

Level* Level::prefab0()
{
  Level* level = new Level("Basic Training");

  // create objects
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(20.0, 1.0,  0.0, 0.0));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(20.0, 1.0,  0.0, 10.0));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 10.0, -9.5, 5.0));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 10.0,  9.5, 5.0));

  // staircase
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 1.0, -6.0, 1.0));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 2.0, -4.0, 1.5));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 1.0, -3.0, 1.0));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 3.0, -2.0, 2.0));

  // moving platform
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 0.5, 1.0, 2.5, 0.0, 2.5, 10000));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 5.0, 2.0, 3.0));

  // second moving platform
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 0.5, 4.0, 4.75, 0.0, 1.0, 10000));

  // exit
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 2.0, 0.5,   8.0, 4.75));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Exit(8.0, 5.5, "prefab1"));

  level->player = new Player(-8.5, 0.0);
  return level;
}

Level* Level::prefab1()
{
  Level* level = new Level("As if you were selling Buttons at the Door");

  // create objects
  // the bounding box
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(15.0, 1.0, 7.5, 0.0));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(15.0, 1.0, 7.5, 20.0));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 19.0, 0.5, 10));
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 19.0, 14.5, 10));

  // first level
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(11.0, 1.0, 6.5, 15.0));

  Button* bd = new Button(11.0, 17.0, -1);
  level->graph->insert(SceneGraph::Level::FOREGROUND, bd);
  Door* d = new Door(2.0, 1.0, 13.0, 15.0, false, true);
  level->graph->insert(SceneGraph::Level::FOREGROUND, d);
  d->link(bd);

  // second level
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(11.0, 1.0, 8.5, 10.0));

  // third level
  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Platform(11.0, 1.0, 6.5, 5.0));

  // forth level
  Button* bg = new Button(1.5, 1.0, -1);
  level->graph->insert(SceneGraph::Level::FOREGROUND, bg);

  level->graph->insert(SceneGraph::Level::FOREGROUND,
    new Grid(2.0, 4.0, 8.5, 2.5, 1));


  level->phases.push_back(new SceneGraph());
  level->phases.push_back(new SceneGraph());
  Exit* e = new Exit(13.0, 1.0, ""); // exit with no name means quit!
  e->phase = 1;
  level->phases.back()->insert(SceneGraph::Level::FOREGROUND, e);

  level->player = new Player(1.5, 15.0);
  return level;
}

Level* Level::prefabTest()
{
  Level* level = new Level("Test Scene");

  level->graph = new SceneGraph();
  // create objects
  {
    Object* o = new Object(1.6, 0.6, -0.2, -0.4);
    VisagePolygon* vp = VisagePolygon::triangle(1.6, 0.6, -0.5);
    vp->setColour(0x007F00FF);
    o->setVisage(vp);
    level->graph->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Object(2.0, 0.6, 0.0, -0.4);
    VisagePolygon* vp = VisagePolygon::triangle(2.0, 0.6, 0.5);
    vp->setColour(0x00FF1FFF);
    o->setVisage(vp);
    level->graph->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Object(2.0, 0.4, 0.0, -0.5);
    VisagePolygon* vp = VisagePolygon::triangle(2.0, 0.4, -0.1);
    vp->setColour(0x00AF1FFF);
    o->setVisage(vp);
    level->graph->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Object(0.1, 0.1, -0.75, 0.75);
    VisageComplex* vc = new VisageComplex();
    VisagePolygon* vp = VisagePolygon::circle(0.1, 16);
    vp->setColour(0xFFFFFFFF);
    {
      Animatrix* oflash0 = new Animatrix();
      oflash0->start = 0;
      oflash0->end = 500;
      oflash0->loop = 1000;
      oflash0->startColour = 0xFF0000FF;
      oflash0->endColour = 0xFFFF00FF;
      vp->addAnimatrix(oflash0);
      Animatrix* oflash1 = new Animatrix();
      oflash1->start = 500;
      oflash1->end = 1000;
      oflash1->loop = 1000;
      oflash1->startColour = 0xFFFF00FF;
      oflash1->endColour = 0xFF0000FF;
      vp->addAnimatrix(oflash1);
    }
    {
      Animatrix* oscale0 = new Animatrix();
      oscale0->start = 0;
      oscale0->end = 1000;
      oscale0->loop = 2000;
      oscale0->startScaleX = oscale0->startScaleY = 1.0;
      oscale0->endScaleX = oscale0->endScaleY = 1.3;
      vp->addAnimatrix(oscale0);
      Animatrix* oscale1 = new Animatrix();
      oscale1->start = 1000;
      oscale1->end = 2000;
      oscale1->loop = 2000;
      oscale1->startScaleX = oscale1->startScaleY = 1.3;
      oscale1->endScaleX = oscale1->endScaleY = 1.0;
      vp->addAnimatrix(oscale1);
    }
    vc->add(vp);
    ParticleSystem* ps = new ParticleSystem(1000, 150);
    ps->setParticleImage("img/particle_soft.png");
    ps->setColours(fromInt(0xFFAF00FF), fromInt(0xFF000000));
    ps->lifeMin = 2000;
    ps->lifeMax = 4000;
    ps->sizeStart = 1.0f;
    ps->sizeEnd = 0.0f;
    ps->speedStart = 0.5;
    ps->speedEnd = 0.0;
    vc->add(ps);
    o->setVisage(vc);
    level->graph->insert(SceneGraph::Level::SCENARY, o);
  }
  level->phases.push_back(new SceneGraph());
  {
    Object* o = new Object();
    ParticleSystem* ps = new ParticleSystem(1000, 200);
    ps->setParticleImage("img/particle_soft.png");
    ps->setColours(fromInt(0xE1F0F5FF), fromInt(0xFFFFFF00));
    ps->lifeMin = 2000;
    ps->lifeMax = 3000;
    ps->sizeStart = 1.0f;
    ps->sizeEnd = 0.0f;
    ps->speedStart = 2.0;
    ps->speedEnd = 0.0;
    ps->spray = pi() / 4;
    ps->direction = pi()/2;
    ps->setGravity(true);
    o->setVisage(ps);
    o->x = 2.75;
    o->y = 0.0;
    o->phase = 0;
    level->phases.back()->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Platform(10.0, 0.3, 0.0, -0.85));
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Platform(1.0, 0.3, -2.0, 0.3));
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Platform(1.0, 0.3, -2.50, 1));
  }
  level->phases.push_back(new SceneGraph());
  {
    Object* o = new Platform(1.0, 1.0, -5.0, 0.0, 2.0, 0.0, 5000);
    o->phase = 1;
    level->phases.back()->insert(SceneGraph::Level::FOREGROUND, o);
  }
  level->phases.push_back(new SceneGraph());
  {
    Object* o = new Platform(1.0, 1.0, 5.0, 0.0, 0.0, 2.0, 5000);
    o->phase = 2;
    level->phases.back()->insert(SceneGraph::Level::FOREGROUND, o);
    Button* b = new Button(-2.5, 2, -1);
    b->phase = 2;
    level->phases.back()->insert(SceneGraph::Level::FOREGROUND, b);

    Door* d = new Door(0.2, 1.0, 2.5, -0.2, false);
    d->phase = 2;
    d->link(b);
    level->phases.back()->insert(SceneGraph::Level::FOREGROUND, d);
  }
  level->phases.push_back(new SceneGraph());
  {
    Object* o = new Platform(1.0, 1.0, 0.0, 0.0, 0.0, 2.0, 2000);
    o->phase = 3;
    level->phases.back()->insert(SceneGraph::Level::FOREGROUND, o);
  }

  level->player = new Player(0.0, 0.0);
  return level;
}
