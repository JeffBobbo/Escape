#include "texture.h"

#include "../gli.h"

#include "../util.h"

#include "../colour.h"
#include "../image.h"

VisageTexture::VisageTexture(const std::string& f)
{
  file = f;
  loadTexture(file);
  flip = false;
}

#include <iostream>
void VisageTexture::draw()
{
  Visage::draw();

  bindTexture(file);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);

  STSprite st = getSTCoords(file, sprite);

  if (flip)
  {
    float t = st.s0;
    st.s0 = st.s1;
    st.s1 = t;
  }
  glTexCoord2f(st.s0, st.t0);  glVertex3f(-0.5f, 0.5f, 0.0f);
  glTexCoord2f(st.s0, st.t1);  glVertex3f(-0.5f, -0.5f, 0.0f);
  glTexCoord2f(st.s1, st.t1);  glVertex3f(0.5f, -0.5f, 0.0f);
  glTexCoord2f(st.s1, st.t0);  glVertex3f(0.5f, 0.5f, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}
