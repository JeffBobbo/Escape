#include "texture.h"

#include "../gli.h"

#include "../util.h"

#include "../colour.h"
#include "../image.h"

VisageTexture::VisageTexture(double w, double h, const std::string& f)
{
  // create a quad at the right size
  vertices[0] = -w/2.0; vertices[1] =  h/2.0;
  vertices[2] = -w/2.0; vertices[3] = -h/2.0;
  vertices[4] =  w/2.0; vertices[5] = -h/2.0;
  vertices[6] =  w/2.0; vertices[7] =  h/2.0;
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
  glTexCoord2f(st.s0, st.t0);  glVertex3f(vertices[0], vertices[1], 0.0f);
  glTexCoord2f(st.s0, st.t1);  glVertex3f(vertices[2], vertices[3], 0.0f);
  glTexCoord2f(st.s1, st.t1);  glVertex3f(vertices[4], vertices[5], 0.0f);
  glTexCoord2f(st.s1, st.t0);  glVertex3f(vertices[6], vertices[7], 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}
