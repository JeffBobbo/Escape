#ifndef GUILABEL_H_INCLUDE
#define GUILABEL_H_INCLUDE

#include "element.h"
#include <string>

//#include "../colour.h"

class GUILabel : public GUIElement
{
public:
  GUILabel();
  GUILabel(const std::string&& t, const std::string&& f = "");
  virtual ~GUILabel() {}

  virtual void draw() const;

  void setText(const std::string& t) { text = t; }
  const std::string& getText() const { return text; }

  void setTextColour(const uint32_t& c);

private:
  double col[4];
  std::string text;
  std::string font;
};

void my_stbtt_initfont();

#endif
