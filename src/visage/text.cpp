#include "text.h"

#include "../gli.h"

#include "../util.h"
#include "../fontmanager.h"
#include "../main.h"
#include "../colour.h"

//#include "../../external/rapidjson/include/rapidjson/document.h"
#include "../../external/stb_truetype.h"

VisageText::VisageText()
  : text("")
  , font("sui_generis.ttf")
  , size(12.0f)
{
  col[0] = 1.0;
  col[1] = 1.0;
  col[2] = 1.0;
  col[3] = 1.0;
}

VisageText::VisageText(const std::string& t, const std::string&& f, float sz)
  : text(t)
  , font(f)
  , size(sz)
{
  col[0] = 1.0;
  col[1] = 1.0;
  col[2] = 1.0;
  col[3] = 1.0;
}

/*
void VisageText::fromJSON(const rapidjson::Document& doc)
{
  file = doc["texture"].GetString();
  loadText(file);

  if (doc.HasMember("scrollX"))
    scrollX = doc["scrollX"].GetDouble();
  if (doc.HasMember("scrollY"))
    scrollY = doc["scrollY"].GetDouble();
  if (doc.HasMember("offsetX"))
    offsetX = doc["offsetX"].GetDouble();
  if (doc.HasMember("offsetY"))
    offsetY = doc["offsetY"].GetDouble();
  if (doc.HasMember("repeatX"))
    repeatX = doc["repeatX"].GetDouble();
  if (doc.HasMember("repeatY"))
    repeatY = doc["repeatY"].GetDouble();
}
 */

void VisageText::draw()
{
  Visage::draw();

  glColor4dv(col);
  /*
  glRasterPos2i(0, 0);
  for (auto it : text)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, it);
  */

  const Font& f = fontManager.get(font, size);
  float w, y0, y1;
  f.size(text, w, y0, y1);
  float x = -w/2;
  float y = -y0;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, f.ftex);
  glBegin(GL_QUADS);
  for (char c : text)
  {
    if (c >= ' ')
    {
      stbtt_aligned_quad q;
      stbtt_GetBakedQuad(f.cdata, 512,512, c-' ', &x,&y,&q,1);
      glTexCoord2f(q.s0,q.t1); glVertex2d(q.x0/TILE_SIZE,q.y0/TILE_SIZE);
      glTexCoord2f(q.s1,q.t1); glVertex2d(q.x1/TILE_SIZE,q.y0/TILE_SIZE);
      glTexCoord2f(q.s1,q.t0); glVertex2d(q.x1/TILE_SIZE,q.y1/TILE_SIZE);
      glTexCoord2f(q.s0,q.t0); glVertex2d(q.x0/TILE_SIZE,q.y1/TILE_SIZE);
    }
  }
  glDisable(GL_TEXTURE_2D);
  glEnd();
}

void VisageText::setTextColour(const uint32_t& c)
{
  col[0] = ((c >> 24) & 255) / 255.0;
  col[1] = ((c >> 16) & 255) / 255.0;
  col[2] = ((c >>  8) & 255) / 255.0;
  col[3] = ((c      ) & 255) / 255.0;
}
