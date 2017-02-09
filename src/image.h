#ifndef IMAGE_H_INCLUDE
#define IMAGE_H_INCLUDE

#include <string>
#include <map>
#include <stdint.h>

#include "../external/stb_image.h"
#include "gli.h"

struct AtlasSprite
{
  int32_t x;
  int32_t y;
  int32_t w;
  int32_t h;
};

struct STSprite
{
  double s0, s1, t0, t1;
};

struct Texture
{
  uint8_t* data;
  int32_t width;
  int32_t height;
  int32_t bpp;
  GLuint tex;

  // atlasing information
  std::map<std::string, AtlasSprite> sprites;
};

//uint8_t* loadTexture(const char* const file, uint* texture,
//                            int32_t* width, int32_t* height);

void loadTexture(const std::string& t);
inline void loadTexture(const char* const t)
{
  loadTexture(std::string(t));
}

void dropTexture(const std::string& t);
inline void dropTexture(const char* const t)
{
  dropTexture(std::string(t));
}
void dropAllTextures();

void bindTexture(const std::string& t);
inline void bindTexture(const char* const t)
{
  return bindTexture(std::string(t));
}

GLuint getTexture(const std::string& t);

STSprite getSTCoords(const std::string& t, const std::string& s);
inline STSprite getSTCoords(const char* const t, const char* const s)
{
  return getSTCoords(std::string(t), std::string(s));
}

#endif
