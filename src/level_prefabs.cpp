#include "level.h"

#include "scenegraph.h"
#include "object/allobject.h"
#include "visage/allvisage.h"

#include "util.h"
#include "colour.h"

Level* Level::prefabTest()
{
  Level* level = new Level("Test Scene");

  level->graph = new SceneGraph();
  // create objects
  {
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Wall(50.0, 0.2,   0.0, -6.0));
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Wall( 2.0, 1.0, -14.0, -5.5));
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Wall( 2.0, 2.0, -11.0, -5.0));
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Wall( 2.0, 3.0,  -8.0, -4.5));
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Wall( 2.0, 5.0,   0.0, -1.0));
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Platform(2.0, 0.5, -2.0, -1.0, 0.0, 2.5, 10000));
  }
  /*
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
    ps->setParticleImage("img/particles/soft_glow_alpha_128.png");
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
      new Wall(10.0, 0.3, 0.0, -0.85));
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Wall(1.0, 0.3, -2.0, 0.3));
    level->graph->insert(SceneGraph::Level::FOREGROUND,
      new Wall(1.0, 0.3, -2.50, 1));
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
  */

  level->player = new Player(-22.5, -6.0);
  return level;
}
