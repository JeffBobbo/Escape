#ifndef VISAGEPOLYGON_H_INCLUDE
#define VISAGEPOLYGON_H_INCLUDE

#include "visage.h"

#include <vector>
#include <stdint.h>
#include <GL/gl.h>

#include "../util.h"

class VisagePolygon : public Visage
{
public:
  VisagePolygon() {}
  virtual ~VisagePolygon()
  {
    for (Vec2D* v : vertices)
      delete v;
  }

  static VisagePolygon* rectangle(double u, double v)
  {
    VisagePolygon* vp = new VisagePolygon();
    vp->vertices.push_back(new Vec2D(-u/2, -v/2));
    vp->vertices.push_back(new Vec2D( u/2, -v/2));
    vp->vertices.push_back(new Vec2D( u/2,  v/2));
    vp->vertices.push_back(new Vec2D(-u/2,  v/2));
    return vp;
  }
  static VisagePolygon* square(double u)
  {
    return rectangle(u, u);
  }
  static VisagePolygon* triangle(double width, double height)
  {
    VisagePolygon* vp = new VisagePolygon();
    vp->vertices.push_back(new Vec2D(-width/2, -height/2));
    vp->vertices.push_back(new Vec2D(width/2.0, -height/2));
    vp->vertices.push_back(new Vec2D(0.0, height/2));
    return vp;
  }

  virtual void draw()
  {
    double offsetX = 0.0;
    double offsetY = 0.0;
    for (const Animatrix* const a : animatrices)
    {
      if (!a->isActive())
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

  inline const uint32_t& getColour() const { return colour; }
  inline void setColour(uint32_t c) { colour = c; }

private:
  std::vector<Vec2D* > vertices;
  uint32_t colour; // temp
};

#endif
