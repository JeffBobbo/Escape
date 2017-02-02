#include "image.h"

#include <map>
#include <iostream>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#include "gli.h"

std::map<std::string, Texture> texmap;

/*
uint8_t* loadTexture(const char* const file, uint* texture,
                            int32_t* width, int32_t* height)
{
  int32_t bpp;
  uint8_t* data = stbi_load(file, width, height, &bpp, 4);
  if (!data)
  {
    printf("%s\n", stbi_failure_reason());
  }

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
  return data;
}
 */

void loadTexture(const std::string& t)
{
  if (texmap.find(t) != std::end(texmap))
    return;

  Texture tex;
  tex.data = stbi_load(t.c_str(), &tex.width, &tex.height, &tex.bpp, 4);
  if (!tex.data)
  {
    std::cerr << "Failed to load image: " << t << std::endl;
    exit(1); // die
  }
  glGenTextures(1, &tex.tex);
  glBindTexture(GL_TEXTURE_2D, tex.tex);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

  texmap.insert(std::make_pair(t, tex));
}

void dropTexture(const std::string& t)
{
  auto it = texmap.find(t);
  if (it != std::end(texmap))
  {
    stbi_image_free(it->second.data);
    texmap.erase(it);
  }
}
void dropAllTextures()
{
  for (auto it : texmap)
    stbi_image_free(it.second.data);
  texmap.clear();
}

uint8_t* getTexture(const std::string& t, int32_t& width, int32_t& height)
{
  auto it = texmap.find(t);
  if (it == std::end(texmap))
  {
    loadTexture(t);
    it = texmap.find(t);
  }
  width = it->second.width;
  height = it->second.height;
  return it->second.data;
}
