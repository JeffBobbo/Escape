#ifndef VISAGEPOLYGON_H_INCLUDE
#define VISAGEPOLYGON_H_INCLUDE

#include "visage.h"

#include <vector>
#include <stdint.h>

#include "../util.h"

class VisagePolygon : public Visage
{
protected:
  VisagePolygon() : colour(0xFFFFFFFF) {}
public:
  virtual ~VisagePolygon()
  {
    for (Vec2D* v : vertices)
      delete v;
  }

  static VisagePolygon* rectangle(double w, double h);
  static VisagePolygon* triangle(double b, double h, double offset = 0.0);
  static VisagePolygon* circle(double r, uint32_t points);

  virtual inline Type type() const { return Type::POLYGON; }
  inline const uint32_t& getColour() const { return colour; }
  inline void setColour(uint32_t c) { colour = c; }

  virtual void draw();

private:
  std::vector<Vec2D* > vertices;
  uint32_t colour;
};

#endif
