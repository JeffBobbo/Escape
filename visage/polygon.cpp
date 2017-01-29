#include "polygon.h"

#include <GL/gl.h>

#include "../util.h"

VisagePolygon* VisagePolygon::rectangle(double u, double v)
{
  VisagePolygon* vp = new VisagePolygon();
  vp->vertices.push_back(new Vec2D(-u/2, -v/2));
  vp->vertices.push_back(new Vec2D( u/2, -v/2));
  vp->vertices.push_back(new Vec2D( u/2,  v/2));
  vp->vertices.push_back(new Vec2D(-u/2,  v/2));
  return vp;
}
VisagePolygon* VisagePolygon::square(double u)
{
  return rectangle(u, u);
}
VisagePolygon* VisagePolygon::triangle(double width, double height, double offset)
{
  VisagePolygon* vp = new VisagePolygon();
  vp->vertices.push_back(new Vec2D(-width/2.0, -height/2.0));
  vp->vertices.push_back(new Vec2D(width/2.0, -height/2.0));
  vp->vertices.push_back(new Vec2D(width*offset-width/2.0, height/2));
  return vp;
}
VisagePolygon* VisagePolygon::circle(double radius, uint32_t points)
{
  VisagePolygon* vp = new VisagePolygon();
  // calculate angle between points
  // take the negative, we want our vertices to go anticlockwise
  const double increment = -(2 * Pi()) / points;
  for (uint32_t i = 0; i < points; ++i)
  {
    double x = radius * std::cos(increment * i);
    double y = radius * std::sin(increment * i);
    vp->vertices.push_back(new Vec2D(x, y));
  }
  return vp;
}

#include "../colour.h"
#include <iostream>
void VisagePolygon::draw()
{
  double offsetX = 0.0;
  double offsetY = 0.0;
  double angle = 0.0;
  double scalex = 1.0;
  double scaley = 1.0;
  double r = ((colour >> 24) & 255) / 255.0; // r
  double g = ((colour >> 16) & 255) / 255.0; // g
  double b = ((colour >> 8 ) & 255) / 255.0; // b
  double a = ((colour      ) & 255) / 255.0; // a
  for (const Animatrix* const ani : animatrices)
  {
    if (!ani->isActive())
      continue;
    if (!ani->isVisible())
      continue;
    offsetX += ani->startX;
    offsetY += ani->startY;

    if (ani->loop != 0)
    {
      const double p = (tickCount() % (ani->end-ani->start)) / static_cast<double>(ani->end-ani->start);

      if (ani->startColour != ani->endColour)
      {
        RGBA cf = interpolate(fromInt(ani->startColour), fromInt(ani->endColour), p);
        r *= cf.r;
        g *= cf.g;
        b *= cf.b;
        a *= cf.a;
      }

      if (ani->startScaleX != ani->endScaleX)
        scalex *= interpolate(ani->startScaleX, ani->endScaleX, p);
      if (ani->startScaleY != ani->endScaleY)
        scaley *= interpolate(ani->startScaleY, ani->endScaleY, p);
    }
  }
  glPushMatrix();
  glTranslatef(offsetX, offsetY, 0.0);
  glRotatef(angle, 0.0, 0.0, 1.0);
  glScalef(scalex, scaley, 1.0);
  glBegin(GL_POLYGON);
  // set the colour
  glColor4f(r, g, b, a);
  for (const Vec2D* const v : vertices)
    glVertex3f(v->x, v->y, 0.0);
  glEnd();
  glPopMatrix();
}
