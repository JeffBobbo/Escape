#include "polygon.h"

#include "../gli.h"

#include "../util.h"

VisagePolygon* VisagePolygon::rectangle()
{
  VisagePolygon* vp = new VisagePolygon();
  vp->vertices.push_back(new Vec2D(-0.5f, -0.5f));
  vp->vertices.push_back(new Vec2D( 0.5f, -0.5f));
  vp->vertices.push_back(new Vec2D( 0.5f,  0.5f));
  vp->vertices.push_back(new Vec2D(-0.5f,  0.5f));
  return vp;
}
VisagePolygon* VisagePolygon::triangle(double offset)
{
  VisagePolygon* vp = new VisagePolygon();
  vp->vertices.push_back(new Vec2D(-0.5f, -0.5f));
  vp->vertices.push_back(new Vec2D( 0.5f, -0.5f));
  vp->vertices.push_back(new Vec2D(offset, 0.5f));
  return vp;
}
VisagePolygon* VisagePolygon::circle(uint32_t points)
{
  VisagePolygon* vp = new VisagePolygon();
  // calculate angle between points
  // take the negative, we want our vertices to go anticlockwise
  const double increment = -(2 * pi()) / points;
  for (uint32_t i = 0; i < points; ++i)
  {
    double x = std::cos(increment * i);
    double y = std::sin(increment * i);
    vp->vertices.push_back(new Vec2D(x, y));
  }
  return vp;
}

#include "../colour.h"
#include <iostream>
void VisagePolygon::draw()
{
  glColor4f(
    ((colour >> 24) & 255) / 255.0, // r
    ((colour >> 16) & 255) / 255.0, // g
    ((colour >> 8 ) & 255) / 255.0, // b
    ((colour      ) & 255) / 255.0); // a

  Visage::draw();

  glBegin(GL_POLYGON);
  for (const Vec2D* const v : vertices)
    glVertex3f(v->x, v->y, 0.0);
  glEnd();
  glPopMatrix();
}
