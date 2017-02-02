#include "texture.h"

#include "../gli.h"

#include "../util.h"

#include "../colour.h"
#include "../image.h"

VisageTexture::VisageTexture(const std::string& f)
{
  file = f;
  loadTexture(file);
  rows = 1;
  columns = 1;
  sprite_r = 0;
  sprite_c = 0;
  flip = false;
}

#include <iostream>
void VisageTexture::draw()
{
  int32_t w, h;
  uint8_t* d = getTexture(file, w, h);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d);

  glEnable(GL_TEXTURE_2D);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);

  float uw = 1.0f / columns;
  float u0 = sprite_c * uw;
  float u1 = (sprite_c+1) * uw;
  float vw = 1.0f / rows;
  float v0 = sprite_r * vw;
  float v1 = (sprite_r+1) * vw;

  if (flip)
  {
    float t = u0;
    u0 = u1;
    u1 = t;
  }
  glTexCoord2f(u0, v0);  glVertex3f(-0.5f, 0.5f, 0.0f);
  glTexCoord2f(u0, v1);  glVertex3f(-0.5f, -0.5f, 0.0f);
  glTexCoord2f(u1, v1);  glVertex3f(0.5f, -0.5f, 0.0f);
  glTexCoord2f(u1, v0);  glVertex3f(0.5f, 0.5f, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}
