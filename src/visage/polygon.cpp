#include "polygon.h"

#include "../gli.h"

#include "../util.h"

VisagePolygon* VisagePolygon::rectangle(double w, double h)
{
  VisagePolygon* vp = new VisagePolygon();
  vp->vertices.push_back(new Vec2D(-w/2.0,  h/2.0));
  vp->vertices.push_back(new Vec2D(-w/2.0, -h/2.0));
  vp->vertices.push_back(new Vec2D( w/2.0, -h/2.0));
  vp->vertices.push_back(new Vec2D( w/2.0,  h/2.0));
  return vp;
}
VisagePolygon* VisagePolygon::triangle(double b, double h, double offset)
{
  VisagePolygon* vp = new VisagePolygon();
  vp->vertices.push_back(new Vec2D(-b/2.0, -h/2.0));
  vp->vertices.push_back(new Vec2D( b/2.0, -h/2.0));
  vp->vertices.push_back(new Vec2D(b*offset,  h/2.0));
  return vp;
}
VisagePolygon* VisagePolygon::circle(double r, uint32_t points)
{
  VisagePolygon* vp = new VisagePolygon();
  // calculate angle between points
  // take the negative, we want our vertices to go anticlockwise
  const double increment = -(2 * pi()) / points;
  for (uint32_t i = 0; i < points; ++i)
  {
    double x = r * std::cos(increment * i);
    double y = r * std::sin(increment * i);
    vp->vertices.push_back(new Vec2D(x, y));
  }
  return vp;
}

void VisagePolygon::draw()
{
  double col[4];
  glGetDoublev(GL_CURRENT_COLOR, col);

  glColor4f(
    col[0] * ((colour >> 24) & 255) / 255.0, // r
    col[1] * ((colour >> 16) & 255) / 255.0, // g
    col[2] * ((colour >> 8 ) & 255) / 255.0, // b
    col[3] * ((colour      ) & 255) / 255.0); // a

  Visage::draw();

  glBegin(GL_POLYGON);
  for (const Vec2D* const v : vertices)
    glVertex3f(v->x, v->y, 0.0);
  glEnd();
  glPopMatrix();
}
