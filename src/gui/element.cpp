#include "element.h"

GUIElement::GUIElement()
  : x0(0), y0(0), x1(0), y1(0)
{
}

void GUIElement::setPosition(int32_t x, int32_t y)
{
  int32_t w = x1 - x0;
  int32_t h = y1 - y0;
  x0 = x;
  x1 = x+w;
  y0 = y;
  y1 = y+h;
}
void GUIElement::setSize(int32_t w, int32_t h)
{
  x1 = x0 + w;
  y1 = y0 + h;
}
