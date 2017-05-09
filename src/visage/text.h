#ifndef VISAGETEXT_H_INCLUDE
#define VISAGETEXT_H_INCLUDE

#include "visage.h"

#include <string>
#include <stdint.h>

#include "../util.h"
#include "../gli.h"

class VisageText : public Visage
{
public:
  VisageText();
  VisageText(const std::string&& t, const std::string&& f, float sz);
  virtual ~VisageText() {}

  virtual inline Type type() const { return Type::TEXT; }
  //virtual void fromJSON(const rapidjson::Document& doc);


  virtual void draw();

  void setText(const std::string& t) { text = t; }
  const std::string& getText() const { return text; }

  void setTextColour(const uint32_t& c);
  void setFont(const std::string& f) { font = f; }
  void setFontSize(const float sz) { size = sz; }

private:
  double col[4];
  std::string text;
  std::string font;
  float size;
};

#endif
