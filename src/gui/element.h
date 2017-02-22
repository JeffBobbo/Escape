#ifndef GUIELEMENT_H_INCLUDE
#define GUIELEMENT_H_INCLUDE

#include <stdint.h>

class GUIElement
{
public:
  GUIElement();
  virtual ~GUIElement() {}

  virtual void draw() const = 0;

  virtual void setPosition(int32_t w, int32_t x, int32_t y, int32_t z);
  virtual void setRelative(double x0, double y0, double x1, double y1);
  virtual void getPosition(int32_t& w, int32_t& x, int32_t& y, int32_t& z) const;
  //virtual void getSize(int32_t& w, int32_t& h) const;
  virtual void setParent(GUIElement* e) { parent = e; }

protected:
  int32_t x0, y0, x1, y1;
  double px0, py0, px1, py1;
  GUIElement* parent;
};

#endif
