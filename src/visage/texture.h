#ifndef VISAGETEXTURE_H_INCLUDE
#define VISAGETEXTURE_H_INCLUDE

#include "visage.h"

#include <string>
#include <stdint.h>

#include "../util.h"
#include "../gli.h"

class VisageTexture : public Visage
{
public:
  VisageTexture();
  VisageTexture(double w, double h, const std::string& file, double sx = 0.0, double sy = 0.0);
  virtual ~VisageTexture() {}

  virtual inline Type type() const { return Type::TEXTURE; }
  //virtual void fromJSON(const rapidjson::Document& doc);


  void setAtlasSprite(const std::string& s) { sprite = s; }
  void setAtlasSprite(const std::string&& s) { sprite = s; }
  void setFlip(bool f) { flip = f; }
  void setSize(double w, double h);
  void setRepeat(double rx, double ry) { repeatX = rx; repeatY = ry; }
  virtual void draw();

private:
  float vertices[8];
  std::string file;
  std::string sprite;
  bool flip;
  double scrollX, scrollY, offsetX, offsetY;
  double repeatX, repeatY;
};

#endif
