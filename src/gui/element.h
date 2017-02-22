#ifndef GUIELEMENT_H_INCLUDE
#define GUIELEMENT_H_INCLUDE

#include <stdint.h>

class GUIElement
{
public:
  GUIElement();
  virtual ~GUIElement() {}

  virtual void draw() const = 0;

  virtual void setPosition(int32_t x, int32_t y);
  virtual void setSize(int32_t w, int32_t h);

protected:
  int32_t x0, y0, x1, y1;
  //double px0, py0, px1, py1;
};

#endif
