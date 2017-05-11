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
  level->insert(SceneGraph::Level::BACKGROUND, bg);
  return level;
}

Level* Level::prefab0()
{
  Level* level = new Level("Basic Training");

  // create objects
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(20.0, 1.0,  0.0, 0.0));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(20.0, 1.0,  0.0, 10.0));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 10.0, -9.5, 5.0));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 10.0,  9.5, 5.0));

  // staircase
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 1.0, -6.0, 1.0));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 2.0, -4.0, 1.5));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 1.0, -3.0, 1.0));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 3.0, -2.0, 2.0));

  level->insert(SceneGraph::Level::FOREGROUND,
    new Checkpoint(-2.0, 4.0));

  level->insert(SceneGraph::Level::NPC,
    new Follower(0.1, 0.1, -2.0, 4.0));

  level->insert(SceneGraph::Level::NPC,
    new Turret(-2.75, 3.0));

  // moving platform
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 0.25, 1.0, 2.875, 0.0, 2.55, 10000));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 1.0, 5.0, 2.0, 3.0));

  // second moving platform
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 0.25, 4.0, 4.75, 0.0, 0.0, 1));

  Pusher* p = new Pusher(0.5, 0.5, 2.75, 0.75);
  p->setAttributes(90.0, 0.0, 10.0, 0.5);
  level->insert(SceneGraph::Level::FOREGROUND, p);

  // exit
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform( 2.0, 0.5,   8.0, 4.75));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Exit(8.0, 5.75, "prefab1"));

  level->addPlayer(new Player(-8.5, 1.0));
  return level;
}

Level* Level::prefab1()
{
  Level* level = new Level("As if you were selling Buttons at the Door");

  // create objects
  // the bounding box
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(15.0, 1.0, 7.5, 0.0));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(15.0, 1.0, 7.5, 20.0));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 19.0, 0.5, 10));
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1.0, 19.0, 14.5, 10));

  // first level
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(11.0, 1.0, 6.5, 15.0));

  Button* bd = new Button(11.0, 16.0, -1);
  level->insert(SceneGraph::Level::FOREGROUND, bd);
  Door* d = new Door(2.0, 1.0, 13.0, 15.0, false, true);
  level->insert(SceneGraph::Level::FOREGROUND, d);
  d->link(bd);

  // second level
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(11.0, 1.0, 8.5, 10.0));

  // third level
  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(11.0, 1.0, 6.5, 5.0));

  // forth level
  Button* be = new Button(1.5, 1.0, -1);
  level->insert(SceneGraph::Level::FOREGROUND, be);

  Exit* e = new Exit(13.0, 1.0); // exit with no name means quit!
  be->link(e);
  level->insert(SceneGraph::Level::FOREGROUND, e);

  level->addPlayer(new Player(1.5, 16.0));
  return level;
}

Level* Level::prefabTest()
{
  Level* level = new Level("Test Scene");

  // create objects
  {
    Object* o = new Object(1.6, 0.6, -0.2, -0.4);
    VisagePolygon* vp = VisagePolygon::triangle(1.6, 0.6, -0.5);
    vp->setColour(0x007F00FF);
    o->setVisage(vp);
    level->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Object(2.0, 0.6, 0.0, -0.4);
    VisagePolygon* vp = VisagePolygon::triangle(2.0, 0.6, 0.5);
    vp->setColour(0x00FF1FFF);
    o->setVisage(vp);
    level->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Object(2.0, 0.4, 0.0, -0.5);
    VisagePolygon* vp = VisagePolygon::triangle(2.0, 0.4, -0.1);
    vp->setColour(0x00AF1FFF);
    o->setVisage(vp);
    level->insert(SceneGraph::Level::SCENARY, o);
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
    level->insert(SceneGraph::Level::SCENARY, o);
  }
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
    o->position = Vec2D(2.75, 0.0);
    level->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    level->insert(SceneGraph::Level::FOREGROUND,
      new Platform(10.0, 0.3, 0.0, -0.85));
    level->insert(SceneGraph::Level::FOREGROUND,
      new Platform(1.0, 0.3, -2.0, 0.3));
    level->insert(SceneGraph::Level::FOREGROUND,
      new Platform(1.0, 0.3, -2.50, 1));
  }
  {
    Object* o = new Platform(1.0, 1.0, -5.0, 0.0, 2.0, 0.0, 5000);
    level->insert(SceneGraph::Level::FOREGROUND, o);
  }
  {
    Object* o = new Platform(1.0, 1.0, 5.0, 0.0, 0.0, 2.0, 5000);
    level->insert(SceneGraph::Level::FOREGROUND, o);
    Button* b = new Button(-2.5, 2, -1);
    level->insert(SceneGraph::Level::FOREGROUND, b);

    Door* d = new Door(0.2, 1.0, 2.5, -0.2, false);
    d->link(b);
    level->insert(SceneGraph::Level::FOREGROUND, d);
  }
  {
    Object* o = new Platform(1.0, 1.0, 0.0, 0.0, 0.0, 2.0, 2000);
    level->insert(SceneGraph::Level::FOREGROUND, o);
  }

  level->addPlayer(new Player(0.0, 0.0));
  return level;
}

Level* Level::prefabTestTurret()
{
  Level* level = new Level("Turret Test");

  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(10.0, 0.3, 0.0, -0.85));

  level->insert(SceneGraph::Level::NPC,
    new Turret(-2.75, 0.5));

  level->addPlayer(new Player(0.0, 0.0));

  return level;
}

Level* Level::prefabTestPusher()
{
  Level* level = new Level("Pusher Test");

  level->insert(SceneGraph::Level::FOREGROUND,
    new Platform(1000.0, 1.0, 0.0, 0.0));

  Pusher* p = new Pusher(0.5, 0.5, -5.0, 0.5);
  p->setAttributes(90, 0.0, 10.0, 0.5);
  level->insert(SceneGraph::Level::FOREGROUND, p);

  p = new Pusher(0.5, 0.5, 5.0, 0.5);
  p->setAttributes(45, 0.0, 20.0, 0.5);
  level->insert(SceneGraph::Level::FOREGROUND, p);

  level->addPlayer(new Player(0.0, 0.0));

  return level;
}

Level* Level::escape0()
{
  Level* level = new Level("The Chamber");

  {
    Platform* ground = new Platform(20.0, 1.0, 10.0, 0.5);
    level->insert(SceneGraph::Level::FOREGROUND, ground);
    Platform* wallLeft = new Platform(1.0, 10.0, 0.5, 6.0);
    level->insert(SceneGraph::Level::FOREGROUND, wallLeft);
    Platform* wallRight = new Platform(1.0, 5.0, 7.5, 3.5);
    level->insert(SceneGraph::Level::FOREGROUND, wallRight);
    Platform* cellCeil = new Platform(7.0, 1.0, 4.5, 7.5);
    level->insert(SceneGraph::Level::FOREGROUND, cellCeil);
  }

  {
    Pusher* p = new Pusher(0.5, 0.5, 6.75, 1.25);
    Button* bd = new Button(6.5, 1.25, -1, "DESTROY THE AIR CONDITIONING UNIT");
    p->setAttributes(90, 0.0, 10.0, 0.5);
    level->insert(SceneGraph::Level::FOREGROUND, p);
    Door* d = new Door(0.5, 0.5, 6.75, 1.25, false);
    d->link(bd);
    level->insert(SceneGraph::Level::FOREGROUND, d);
    level->insert(SceneGraph::Level::FOREGROUND, bd);
  }

  {
    Camera* c = new Camera(1.25, 4.0);
    level->insert(SceneGraph::Level::NPC, c);
  }

  level->addPlayer(new Player(1.5, 1.5));
  return level;
}
