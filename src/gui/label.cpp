#include "label.h"

#include "../gli.h"

GUILabel::GUILabel()
  : GUIElement()
  , text("")
{
}

GUILabel::GUILabel(const std::string&& t)
  : GUIElement()
  , text(t)
{
  col[0] = 1.0;
  col[1] = 1.0;
  col[2] = 1.0;
  col[3] = 1.0;
}

void GUILabel::setTextColour(const uint32_t& c)
{
  col[0] = ((c >> 24) & 255) / 255.0;
  col[1] = ((c >> 16) & 255) / 255.0;
  col[2] = ((c >>  8) & 255) / 255.0;
  col[3] = ((c      ) & 255) / 255.0;
}

void GUILabel::draw() const
{
  if (!isVisible())
    return;
  glColor4d(col[0], col[1], col[2], col[3]);
  int32_t a, b, c, d;
  getPosition(a, b, c, d);
  glRasterPos2i(a, b+(d-b)/2);

  for (auto it : text)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, it);
}
