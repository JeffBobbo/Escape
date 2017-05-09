#include "label.h"

#include "../gli.h"

#include "../main.h"
#include "../fontmanager.h"
#include "../../external/stb_truetype.h"

GUILabel::GUILabel()
  : GUIElement()
  , text("")
  , font(""), size(12.0f)
{
  col[0] = 1.0;
  col[1] = 1.0;
  col[2] = 1.0;
  col[3] = 1.0;
}

GUILabel::GUILabel(const std::string&& t, const std::string&& f, float sz)
  : GUIElement()
  , text(t)
  , font(f), size(sz)
{
  col[0] = 1.0;
  col[1] = 1.0;
  col[2] = 1.0;
  col[3] = 1.0;
}

void GUILabel::getPosition(int32_t& w, int32_t& x, int32_t& y, int32_t& z) const
{
  int32_t p = 0, q = 0, r = 0, s = 0;
  float a = 0.0f, b = 0.0f, c = 0.0f;
  if (font.length())
    fontManager.get(font, size).size(text, a, b, c);
  if (parent)
  {
    parent->getPosition(p, q, r, s);
    w = p + static_cast<int32_t>(px0 * (r-p) + x0 + -a/2);
    x = q + static_cast<int32_t>(py0 * (s-q) + y0 +  b);
    y = p + static_cast<int32_t>(px1 * (r-p) + x1 + a/2);
    z = q + static_cast<int32_t>(py1 * (s-q) + y1 + c);
  }
  else
  {
    w = static_cast<int32_t>(px0 * screenWidth  + x0 + -a/2);
    x = static_cast<int32_t>(py0 * screenHeight + y0 + b);
    y = static_cast<int32_t>(px1 * screenWidth  + x1 + a/2);
    z = static_cast<int32_t>(py1 * screenHeight + y1 + c);
  }
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
  glColor4d(col[0], col[1], col[2], 1.0);//col[3]);
  int32_t a, b, c, d;
  getPosition(a, b, c, d);

  if (font.length() == 0)
  {
    glRasterPos2i(a, b+(d-b)/2);
    for (auto it : text)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, it);
  }
  else
  {
    const Font& f = fontManager.get(font, size);
    float x = a;
    float y = b;
    float w, y0, y1;
    f.size(text, w, y0, y1);
    y -= y0;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, f.ftex);
    glBegin(GL_QUADS);
    for (char c : text)
    {
      if (c >= ' ')
      {
        stbtt_aligned_quad q;
        stbtt_GetBakedQuad(f.cdata, 512,512, c-' ', &x,&y,&q,1);
        glTexCoord2f(q.s0,q.t0); glVertex2f(q.x0,q.y0);
        glTexCoord2f(q.s1,q.t0); glVertex2f(q.x1,q.y0);
        glTexCoord2f(q.s1,q.t1); glVertex2f(q.x1,q.y1);
        glTexCoord2f(q.s0,q.t1); glVertex2f(q.x0,q.y1);
      }
    }
    glDisable(GL_TEXTURE_2D);
    glEnd();
  }
}
