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

      HSVA c0 = hsva({
        ((ani->startColour >> 24) & 255) / 255.0,
        ((ani->startColour >> 16) & 255) / 255.0,
        ((ani->startColour >>  8) & 255) / 255.0,
        ((ani->startColour      ) & 255) / 255.0
      });
      HSVA c1 = hsva({
        ((ani->endColour >> 24) & 255) / 255.0,
        ((ani->endColour >> 16) & 255) / 255.0,
        ((ani->endColour >>  8) & 255) / 255.0,
        ((ani->endColour      ) & 255) / 255.0
      });

      RGBA cf = rgba({
        interpolate(c0.h, c1.h, p),
        interpolate(c0.s, c1.s, p),
        interpolate(c0.v, c1.v, p),
        interpolate(c0.a, c1.a, p)
      });
      r *= cf.r;
      g *= cf.g;
      b *= cf.b;
      a *= cf.a;

      /*
      uint8_t startR = (ani->startColour >> 24) & 255;
      uint8_t startG = (ani->startColour >> 16) & 255;
      uint8_t startB = (ani->startColour >>  8) & 255;
      uint8_t startA = (ani->startColour      ) & 255;
      uint8_t endR = (ani->endColour >> 24) & 255;
      uint8_t endG = (ani->endColour >> 16) & 255;
      uint8_t endB = (ani->endColour >>  8) & 255;
      uint8_t endA = (ani->endColour      ) & 255;
      const double p = (tickCount() % (ani->end-ani->start)) / static_cast<double>(ani->end-ani->start);
      r *= interpolate(startR, endR, p) / 255.0;
      g *= interpolate(startG, endG, p) / 255.0;
      b *= interpolate(startB, endB, p) / 255.0;
      a *= interpolate(startA, endA, p) / 255.0;
       */
    }
  }
  glBegin(GL_POLYGON);
  // set the colour
  glColor4f(r, g, b, a);
  for (const Vec2D* const v : vertices)
    glVertex3f(v->x+offsetX, v->y+offsetY, 0.0);
  glEnd();
}
