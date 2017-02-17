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
  VisageTexture(double w, double h, const std::string& file, double sx = 0.0, double sy = 0.0);
  virtual ~VisageTexture() {}

  virtual inline Type type() const { return Type::TEXTURE; }

  void setAtlasSprite(const std::string& s) { sprite = s; }
  void setAtlasSprite(const std::string&& s) { sprite = s; }
  void setFlip(bool f) { flip = f; }
  virtual void draw();

private:
  float vertices[8];
  std::string file;
  std::string sprite;
  bool flip;
  double scrollX, scrollY, offsetX, offsetY;
};

#endif
