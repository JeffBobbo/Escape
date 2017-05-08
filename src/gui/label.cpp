#include "label.h"

#include "../gli.h"

GUILabel::GUILabel()
  : GUIElement()
  , text("")
  , font("")
{
}

GUILabel::GUILabel(const std::string&& t, const std::string&& f)
  : GUIElement()
  , text(t)
  , font(f)
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

#define STB_TRUETYPE_IMPLEMENTATION
#include "../../external/stb_truetype.h"

unsigned char ttf_buffer[1<<20];
unsigned char temp_bitmap[512*512];
stbtt_bakedchar cdata[96];
GLuint ftex;

#include <iostream>
void my_stbtt_initfont()
{
  fread(ttf_buffer, 1, 1<<20, fopen("font/sui_generis.ttf", "rb"));
  stbtt_BakeFontBitmap(ttf_buffer,0, 32.0, temp_bitmap,512,512, 32,96, cdata); // no guarantee this fits!
  // can free ttf_buffer at this point
  glGenTextures(1, &ftex);
  glBindTexture(GL_TEXTURE_2D, ftex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
  // can free temp_bitmap at this point
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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
    float x = a;//50;
    float y = b;//50;
    // assume orthographic projection with units = screen pixels, origin at top left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ftex);
    glBegin(GL_QUADS);
    for (char c : text)
    {
      if (c >= 32)// && c < 128)
      {
        stbtt_aligned_quad q;
        stbtt_GetBakedQuad(cdata, 512,512, c-32, &x,&y,&q,1);//1=opengl & d3d10+,0=d3d9
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
