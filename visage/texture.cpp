#include "texture.h"

#include "../gli.h"

#include "../util.h"

#include "../colour.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"


VisageTexture::VisageTexture(const std::string& file)
{
  data = stbi_load(file.c_str(), &width, &height, &bpp, 4);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
}

void VisageTexture::draw()
{
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

  glEnable(GL_TEXTURE_2D);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-0.5f, 0.5f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-0.5f, -0.5f, 0.0f);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(0.5f, -0.5f, 0.0f);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(0.5f, 0.5f, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}
