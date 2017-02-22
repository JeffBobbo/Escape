#include "element.h"

#include "../main.h"

GUIElement::GUIElement()
  : x0(0), y0(0), x1(0), y1(0)
  , px0(0.0), py0(0.0), px1(0.0), py1(0.0)
  , parent(nullptr)
{
}

void GUIElement::setPosition(int32_t w, int32_t x, int32_t y, int32_t z)
{
  x0 = w;
  x1 = y;
  y0 = x;
  y1 = z;
}
void GUIElement::setRelative(double x0, double y0, double x1, double y1)
{
  px0 = x0;
  py0 = y0;
  px1 = x1;
  py1 = y1;
}
void GUIElement::getPosition(int32_t& w, int32_t& x, int32_t& y, int32_t& z) const
{
  int32_t p = 0, q = 0, r = 0, s = 0;
  if (parent)
  {
    parent->getPosition(p, q, r, s);
    w = p + px0 * (r-p) + x0;
    x = q + py0 * (s-q) + y0;
    y = p + px1 * (r-p) + x1;
    z = q + py1 * (s-q) + y1;
  }
  else
  {
    w = px0 * screenWidth  + x0;
    x = py0 * screenHeight + y0;
    y = px1 * screenWidth  + x1;
    z = py1 * screenHeight + y1;
  }
}
/*
void GUIElement::getSize(int32_t& w, int32_t& h) const
{
  int32_t p0, q0, p1, q1;
  if (parent)
  {
    int32_t pWidth, pHeight;
    parent->getSize(pWidth, pHeight);
    p0 = pWidth * px0 + x0;
    q0 = pHeight * py0 + y0;
    p1 = pWidth * px1 + x1;
    q1 = pHeight * px1 + y1;
  }
  else
  {
    p0 = screenWidth * px0 + x0;
    q0 = screenHeight * py0 + y0;
    p1 = screenWidth * px1 + x1;
    q1 = screenHeight * px1 + y1;
  }
  w = p1 - p0;
  h = q1 - q0;
}
 */
