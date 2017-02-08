#ifndef VISAGETEXTURE_H_INCLUDE
#define VISAGETEXTURE_H_INCLUDE

#include "visage.h"

#include <string>
#include <stdint.h>

#include "../util.h"
#include "../gli.h"

#include "../../external/stb_image.h"

class VisageTexture : public Visage
{
public:
  VisageTexture(const std::string& file);
  virtual ~VisageTexture()
  {
  }

  virtual inline Type type() const { return Type::TEXTURE; }

  void setAtlasSize(int32_t r, int32_t c) { rows = r; columns = c; }
  void setAtlasSprite(int32_t x, int32_t y) { sprite_c = x; sprite_r = y; }
  void setFlip(bool f) { flip = f; }
  virtual void draw();

private:
  float vertices[12];
  std::string file;
  int32_t rows;
  int32_t columns;
  int32_t sprite_r;
  int32_t sprite_c;
  bool flip;
};

#endif
