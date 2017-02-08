#ifndef IMAGE_H_INCLUDE
#define IMAGE_H_INCLUDE

#include <string>
#include <stdint.h>

#include "../external/stb_image.h"
#include "gli.h"

struct Texture
{
  uint8_t* data;
  int32_t width;
  int32_t height;
  int32_t bpp;
  GLuint tex;

  // atlasing information
  int32_t rows;
  int32_t columns;
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

GLuint getTexture(const std::string& t);
inline GLuint getTexture(const char* const t)
{
  return getTexture(std::string(t));
}

#endif
