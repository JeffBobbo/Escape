#ifndef IMAGE_H_INCLUDE
#define IMAGE_H_INCLUDE

#include <map>
#include <string>
#include <stdint.h>

#include "external/stb_image.h"

struct Texture
{
  uint8_t* data;
  int32_t width;
  int32_t height;
  int32_t bpp;

  // atlasing information
  int32_t rows;
  int32_t columns;
};

std::map<char*, Texture> texmap;

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

uint8_t* getTexture(const std::string& t);
inline uint8_t* getTexture(const char* const t)
{
  return getTexture(std::string(t));
}

#endif
