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
  VisageText(const std::string& str);
  virtual ~VisageText() {}

  virtual inline Type type() const { return Type::TEXT; }
  //virtual void fromJSON(const rapidjson::Document& doc);


  virtual void draw();

private:
  std::string text;
};

#endif
