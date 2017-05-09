#ifndef GUILABEL_H_INCLUDE
#define GUILABEL_H_INCLUDE

#include "element.h"
#include <string>

//#include "../colour.h"

class GUILabel : public GUIElement
{
public:
  enum class Alignment
  {
    LEFT,
    CENTRE
  };

  GUILabel();
  GUILabel(const std::string&& t, const std::string&& f = "", float sz = 12);
  virtual ~GUILabel() {}

  virtual void draw() const;

  virtual void getPosition(int32_t& w, int32_t& x, int32_t& y, int32_t& z) const;

  void setText(const std::string& t) { text = t; }
  const std::string& getText() const { return text; }

  void setTextColour(const uint32_t& c);
  void setFont(const std::string& f) { font = f; }
  void setFontSize(const float sz) { size = sz; }
  void setAlignment(const Alignment& a) { align = a; }

private:
  double col[4];
  std::string text;
  std::string font;
  float size;
  Alignment align;
};

void my_stbtt_initfont();

#endif
