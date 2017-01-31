#ifndef VISAGETEXTURE_H_INCLUDE
#define VISAGETEXTURE_H_INCLUDE

#include "visage.h"

#include <vector>
#include <stdint.h>

#include "../util.h"
#include "../gli.h"

#include "../external/stb_image.h"

class VisageTexture : public Visage
{
public:
  VisageTexture(const std::string& file);
  virtual ~VisageTexture()
  {
    stbi_image_free(data);
  }

  virtual inline Type type() const { return Type::TEXTURE; }

  virtual void draw();

private:
  float vertices[12];
  GLuint texture;
  uint8_t* data;
  int32_t width, height, bpp;
};

#endif
