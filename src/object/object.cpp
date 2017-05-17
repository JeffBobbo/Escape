#include "object.h"

#include "../main.h"
#include "../gli.h"
#include "../visage/allvisage.h"
#include "platform.h"


Object::Object(Vec2D sz, Vec2D pos)
 : position(std::move(pos))
 , size(std::move(sz))
 , velocity()
 , angle(0.0)
 , visage(nullptr)
 , born(elapsed)
 , attached(nullptr)
 , seppuku(false)
{
}

void Object::idle()
{
}

void Object::move()
{
  Vec2D moveby = velocity * (delta / 1000.0);
  position += moveby;

  if (attached)
    attached->position += moveby;
}

#include <iostream>
void Object::draw()
{
  glPushMatrix();

  // transformations
  glTranslated(position.x, position.y, 0.0);
  glRotated(angle, 0.0, 0.0, 1.0);

  // reset the colour
  glColor4d(1.0, 1.0, 1.0, 1.0);

  // now work out what the colour should be for the phase
  /*
  if (phase >= 0 && phase != level->phasePlayer()) // only needs to be done if we're actually in a phase
  {
    // calculate the phases colour
    double h = (360.0 / level->numPhases()) *  phase;
    RGBA c = rgba({h, 1.0, 1.0, 1.0});

    // calculate the alpha
    double t = (2.0 * pi() / level->numPhases()) * level->phasePlayer();
    double a  = std::fabs(t - h);
    a = (a > pi() ? 2.0 * pi() - a : a) / pi();

    glColor4d(c.r, c.g, c.b, a);
  }
  */
  if (visage)
    visage->draw();

  if (drawBoundingVolumes)
  {
    Vec2D bv = boundingVolume();
    glColor4d(1.0, 0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3d(-bv.x/2.0, -bv.y/2.0, 0.0);
    glVertex3d(-bv.x/2.0,  bv.y/2.0, 0.0);
    glVertex3d( bv.x/2.0,  bv.y/2.0, 0.0);
    glVertex3d( bv.x/2.0, -bv.y/2.0, 0.0);
    glEnd();
  }

  if (drawBoxes)
  {
    glColor4d(0.0, 1.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3d(-size.x/2.0, -size.y/2.0, 0.0);
    glVertex3d(-size.x/2.0,  size.y/2.0, 0.0);
    glVertex3d( size.x/2.0,  size.y/2.0, 0.0);
    glVertex3d( size.x/2.0, -size.y/2.0, 0.0);
    glEnd();
  }

  if (drawPaths && type() == Object::Type::PLATFORM)
    static_cast<Platform*>(this)->drawPath();

  glPopMatrix();
}

void Object::death()
{
  seppuku = true;
}

bool Object::aabbOverlap(const Object* const o) const
{
  Vec2D tb = boundingVolume();
  Vec2D ob = o->boundingVolume();
  const Vec2D& op = o->getPosition();
  return position.x-tb.x/2.0 < op.x+ob.x/2.0 &&
         position.x+tb.x/2.0 > op.x-ob.x/2.0 &&
         position.y-tb.y/2.0 < op.y+ob.y/2.0 &&
         position.y+tb.y/2.0 > op.y-ob.y/2.0;
}

bool Object::pointInside(const Vec2D& v) const
{
  Vec2D bv = boundingVolume();
  return position.x-bv.x/2.0 < v.x &&
         position.x+bv.x/2.0 > v.x &&
         position.y-bv.y/2.0 < v.y &&
         position.y+bv.y/2.0 > v.y;
}

/*
bool Object::satOverlap(const Object* const o) const
{
  Vec2D axis(1.0, -1.0);

  double tProjMin = Vec2D(x, y).dot(axis);
  int tDotMin = 1;
  double tProjMax = tProjMin;
  int tDotMax = 1;

  for ()
}
*/

Object* Object::hitScan(const Object* const o, const bool ethereal) const
{
  if (!o)
    return nullptr;
  if (!level)
    return nullptr;

  //if (phase != o->phase)
    //return nullptr;

  const Vec2D& target = o->getPosition();

  const SceneGraph* const sg = level->getGraph();
  for (auto& layer : *sg)
  {
    for (auto& obj : layer.second)
    {
      if (obj == this) // don't include yourself
        continue;
      if (obj == o) // don't include the target
        continue;
      if ((ethereal || obj->isSolid()) && obj->intersect(position, target))
        return obj;
    }
  }
  return const_cast<Object*>(o);
}

Object* Object::collisionTest(const bool ethereal) const
{
  if (!level)
    return nullptr;

  const SceneGraph* const sg = level->getGraph();
  for (auto& layer : *sg)
  {
    for (auto& obj : layer.second)
    {
      if (obj == this) // don't include yourself
        continue;
      if ((ethereal || obj->isSolid()) && aabbOverlap(obj))
        return obj;
    }
  }
  return nullptr;
}

// intersection algorithm adapted from http://stackoverflow.com/a/100165/5187801
bool Object::intersect(const Vec2D& p0, const Vec2D& p1) const
{
  double minX = p0.x;
  double maxX = p1.x;

  if (p0.x > p1.x)
  {
    minX = p1.x;
    maxX = p0.x;
  }

  Vec2D vol = boundingVolume();
  // Find the intersection of the segment's and rectangle's x-projections
  if (maxX > position.x+vol.x/2.0)
    maxX = position.x+vol.x/2.0;

  if (minX < position.x-vol.x/2.0)
    minX = position.x-vol.x/2.0;

  // if the projections do not intersect then return false
  if (minX > maxX)
    return false;

  // Find corresponding min and max Y for min and max X we found before
  double minY = p0.y;
  double maxY = p1.y;

  double dx = p1.x - p0.x;

  if (std::abs(dx) > 0.0000001)
  {
    double a = (p1.y - p0.y) / dx;
    double b = p0.y - a * p0.x;
    minY = a * minX + b;
    maxY = a * maxX + b;
  }

  if (minY > maxY)
  {
    double tmp = maxY;
    maxY = minY;
    minY = tmp;
  }

  // Find the intersection of the segment's and rectangle's y-projections
  if (maxY > position.y+vol.y/2.0)
    maxY = position.y+vol.y/2.0;

  if (minY < position.y-vol.y/2.0)
    minY = position.y-vol.y/2.0;

  // if the projections do not intersect then return false
  if (minY > maxY)
    return false;

  // there's an intersection
  return true;
}

double Object::angleTo(const Object* const o) const
{
  Vec2D v = o->getPosition() - position;
  return std::atan2(v.y, v.x);
}

/*
Grid::Grid(double w, double h, double u, double v, phase_t p)
  : Object(w, h, u, v)
  , target(p)
  , trigger(nullptr)
{
  visage = new VisageComplex();
  {
    //VisagePolygon* bg = VisagePolygon::rectangle(w, h);
    VisageTexture* bg = new VisageTexture(w, h, "img/background/tile2.png", -0.5, -0.5);
    static_cast<VisageTexture*>(bg)->setRepeat(w, h);
    Animatrix* a0 = new Animatrix();
    a0->startColour = 0xFFFFFF7F;
    a0->endColour   = 0xFFFFFF3F;
    a0->start =    0;
    a0->end   = 1000;
    a0->loop  = 2000;
    bg->addAnimatrix(a0);
    Animatrix* a1 = new Animatrix();
    a1->startColour = 0xFFFFFF3F;
    a1->endColour   = 0xFFFFFF7F;
    a1->start = 1000;
    a1->end   = 2000;
    a1->loop  = 2000;
    bg->addAnimatrix(a1);
    static_cast<VisageComplex*>(visage)->add(bg);
  }
  {
    ParticleSystem* ps = new ParticleSystem(1000, 25);
    ps->setParticleImage("img/particle_soft.png");
    ps->setColours(fromInt(0xFFFFFFFF), fromInt(0xFFFFFF00));
    ps->lifeMin = 1000;
    ps->lifeMax = 1500;
    ps->sizeStart = 1.0f / 8.0f;
    ps->sizeEnd   = 1.0f / 32.0f;
    ps->speedStart = 0.1;
    ps->speedEnd = 0.0;
    ps->offsetX = w;
    ps->offsetY = h;
    ps->rectangle = true;
    //ps->setGravity(true);
    static_cast<VisageComplex*>(visage)->add(ps);
  }
}

void Grid::idle()
{
  if (trigger && trigger->on() == false)
    return;
  if (level->phasePlayer() != target)
  {
    if (aabbOverlap(level->getPlayer()))
      level->getPlayer()->phase = target;
  }
}
*/

