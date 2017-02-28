#ifndef GUIIMAGE_H_INCLUDE
#define GUIIMAGE_H_INCLUDE

#include "element.h"
#include <string>

//#include "../colour.h"

class GUIImage : public GUIElement
{
public:
  GUIImage();
  GUIImage(const std::string&& t);
  virtual ~GUIImage() {}

  virtual void draw() const;

  void setColour(const uint32_t& c);

private:
  double col[4];
  std::string image;
};

#endif
