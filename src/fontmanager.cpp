#include "fontmanager.h"

#include <algorithm>
#include <iostream>
#include <string>

#include <cerrno>
#include <cstring>

#include <stdio.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include "../external/stb_truetype.h"

void Font::size(const std::string& text, float& x, float& y0, float& y1) const
{
  float y = 0.0f;
  x = 0.0f, y0 = 0.0f, y1 = 0.0f;

  for (char c : text)
  {
    if (c >= ' ')
    {
      stbtt_aligned_quad q;
      stbtt_GetBakedQuad(cdata, 512,512, c-' ', &x,&y,&q,1);//1=opengl & d3d10+,0=d3d9
      y0 = std::min(y0, q.y0);
      y1 = std::max(y1, q.y1);
    }
  }
}

FontManager::~FontManager()
{
  while (fonts.size())
  {
    auto it = std::begin(fonts);
    drop(it->first.first, it->first.second);
  }
}

const Font& FontManager::get(const std::string& f, float sz)
{
  auto it = fonts.find(std::make_pair(f, sz));
  if (it == std::end(fonts))
  {
    it = load(f, sz);
	assert(it != std::end(fonts));
  }
  return it->second;
}

std::map<std::pair<std::string, float>, Font>::iterator FontManager::load(const std::string& f, float sz)
{
  unsigned char* ttf_buffer = new unsigned char[1<<20];
  unsigned char* temp_bitmap = new unsigned char[512*512];
  std::string p = "font/" + f;
  std::FILE* fh;
  if (fopen_s(&fh, p.c_str(), "rb"))
  {
    char buf[100];
    strerror_s(buf, 100, errno);
	std::cerr << buf << std::endl;
	throw std::string(buf);
  }
  fread(ttf_buffer, 1, 1 << 20, fh);

  Font font;
  // no guarantee this fits!
  stbtt_BakeFontBitmap(ttf_buffer, 0, sz, temp_bitmap, 512, 512, 32, 96, font.cdata);
  // can free ttf_buffer at this point
  delete[] ttf_buffer;
  glGenTextures(1, &font.ftex);
  glBindTexture(GL_TEXTURE_2D, font.ftex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
  // can free temp_bitmap at this point
  delete[] temp_bitmap;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  return fonts.insert(std::make_pair(std::make_pair(f, sz), font)).first;
}

void FontManager::drop(const std::string& f, float sz)
{
  auto it = fonts.find(std::make_pair(f, sz));
  if (it == std::end(fonts))
    return;

  Font& font = it->second;
  glDeleteTextures(1, &font.ftex);
  fonts.erase(it);
}
