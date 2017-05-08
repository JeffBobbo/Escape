#include "fontmanager.h"

#include <string>

#define STB_TRUETYPE_IMPLEMENTATION
#include "../../external/stb_truetype.h"


void FontManager::load(const std::string& f, double sz)
{
  unsigned char ttf_buffer[1<<20];
  unsigned char temp_bitmap[512*512];
  fread(ttf_buffer, 1, 1 << 20, fopen(f.c_str(), "rb"));
  Font f;
  f.size = sz;
  // no guarantee this fits!
  stbtt_BakeFontBitmap(ttf_buffer, 0, sz, temp_bitmap, 512, 512, 32, 96, f.cdata);
  // can free ttf_buffer at this point
  glGenTextures(1, &f.ftex);
  glBindTexture(GL_TEXTURE_2D, f.ftex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
  // can free temp_bitmap at this point
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  fonts.insert(std::make_pair(std::make_pair(f, sz), f));
}