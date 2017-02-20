#include "texture.h"

#include "../gli.h"

#include "../util.h"

#include "../colour.h"
#include "../image.h"

VisageTexture::VisageTexture(double w, double h, const std::string& f, double sx, double sy)
  : file(f), sprite("")
  , flip(false)
  , scrollX(sx), scrollY(sy), offsetX(0.0), offsetY(0.0)
  , repeatX(1.0), repeatY(1.0)
{
  // create a quad at the right size
  vertices[0] = static_cast<float>(-w/2.0); vertices[1] = static_cast<float>( h/2.0);
  vertices[2] = static_cast<float>(-w/2.0); vertices[3] = static_cast<float>(-h/2.0);
  vertices[4] = static_cast<float>( w/2.0); vertices[5] = static_cast<float>(-h/2.0);
  vertices[6] = static_cast<float>( w/2.0); vertices[7] = static_cast<float>( h/2.0);
  loadTexture(file);
  flip = false;
}

void VisageTexture::draw()
{
  Visage::draw();

  bindTexture(file);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);

  STSprite st;
  if (sprite.size())
    st = getSTCoords(file, sprite);
  else
    st = {(offsetX += scrollX * (delta / 1000.0)),
           offsetX + repeatX,
          (offsetY += scrollY * (delta / 1000.0)),
           offsetY + repeatY
    };

  if (flip)
  {
    double t = st.s0;
    st.s0 = st.s1;
    st.s1 = t;
  }
  glTexCoord2d(st.s0, st.t0);  glVertex3f(vertices[0], vertices[1], 0.0f);
  glTexCoord2d(st.s0, st.t1);  glVertex3f(vertices[2], vertices[3], 0.0f);
  glTexCoord2d(st.s1, st.t1);  glVertex3f(vertices[4], vertices[5], 0.0f);
  glTexCoord2d(st.s1, st.t0);  glVertex3f(vertices[6], vertices[7], 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}
