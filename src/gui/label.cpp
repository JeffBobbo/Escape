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
  glColor4d(col[0], col[1], col[2], col[3]);
  glRasterPos2i(x0, y0);

  for (auto it : text)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, it);
}
