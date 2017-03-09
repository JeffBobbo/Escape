#include "image.h"

#include "../gli.h"
#include "../imageloader.h"

GUIImage::GUIImage()
  : GUIElement()
  , image("")
{
}

GUIImage::GUIImage(const std::string&& t)
  : GUIElement()
  , image(t)
{
  col[0] = 1.0;
  col[1] = 1.0;
  col[2] = 1.0;
  col[3] = 1.0;
}

void GUIImage::draw() const
{
  if (!isVisible())
    return;
  bindTexture(image);
  glColor4d(col[0], col[1], col[2], col[3]);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);

  // calculator the coords
  int32_t a, b, c, d;
  getPosition(a, b, c, d);

  glTexCoord2f(0.0, 1.0);
  glVertex3i(a, b, 0);
  glTexCoord2f(1.0, 1.0);
  glVertex3i(c, b, 0);
  glTexCoord2f(1.0, 0.0);
  glVertex3i(c, d, 0);
  glTexCoord2f(0.0, 0.0);
  glVertex3i(a, d, 0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void GUIImage::setColour(const uint32_t& c)
{
  col[0] = ((c >> 24) & 255) / 255.0;
  col[1] = ((c >> 16) & 255) / 255.0;
  col[2] = ((c >>  8) & 255) / 255.0;
  col[3] = ((c      ) & 255) / 255.0;
}

