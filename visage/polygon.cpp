#include "polygon.h"

#include <GL/gl.h>

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
VisagePolygon* VisagePolygon::triangle(double width, double height)
{
  VisagePolygon* vp = new VisagePolygon();
  vp->vertices.push_back(new Vec2D(-width/2, -height/2));
  vp->vertices.push_back(new Vec2D(width/2.0, -height/2));
  vp->vertices.push_back(new Vec2D(0.0, height/2));
  return vp;
}

void VisagePolygon::draw()
{
  double offsetX = 0.0;
  double offsetY = 0.0;
  for (const Animatrix* const a : animatrices)
  {
    if (!a->isActive())
      continue;
    if (!a->isVisible())
      continue;
    offsetX += a->startX;
    offsetY += a->startY;
  }
  glBegin(GL_POLYGON);
  // set the colour
  glColor4f(
    ((colour >> 24) & 255) / 255.0, // r
    ((colour >> 16) & 255) / 255.0, // g
    ((colour >> 8 ) & 255) / 255.0, // b
    ((colour      ) & 255) / 255.0  // a
  );
  for (const Vec2D* const v : vertices)
    glVertex3f(v->x+offsetX, v->y+offsetY, 0.0);
  glEnd();
}
