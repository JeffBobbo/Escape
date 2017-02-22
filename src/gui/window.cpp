#include "window.h"

#include "../main.h"
#include "../gli.h"

GUIWindow::GUIWindow()
  : GUIElement()
{
  col[0] = 1.0;
  col[1] = 1.0;
  col[2] = 1.0;
  col[3] = 1.0;
}

void GUIWindow::draw() const
{
  glColor4d(col[0], col[1], col[2], col[3]);

  int32_t p0, q0, p1, q1;
  getPosition(p0, q0, p1, q1);

  glBegin(GL_POLYGON);
  glVertex2d(p0, q0);
  glVertex2d(p0, q1);
  glVertex2d(p1, q1);
  glVertex2d(p1, q0);
  glEnd();

  for (auto it : elements)
    it->draw();
}

void GUIWindow::setBackgroundColour(const uint32_t& c)
{
  col[0] = ((c >> 24) & 255) / 255.0;
  col[1] = ((c >> 16) & 255) / 255.0;
  col[2] = ((c >>  8) & 255) / 255.0;
  col[3] = ((c      ) & 255) / 255.0;
}
