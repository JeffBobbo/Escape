#include "text.h"

#include "../gli.h"

#include "../util.h"

#include "../colour.h"

//#include "../../external/rapidjson/include/rapidjson/document.h"

VisageText::VisageText()
  : text("")
{
}

VisageText::VisageText(const std::string& str)
  : VisageText()
{
  text = str;
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

  glColor4d(1.0, 1.0, 1.0, 1.0);
  glRasterPos2i(0, 0);
  for (auto it : text)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, it);

  /*
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
   */
}
