#ifndef FONTMANAGER_H_INCLUDE
#define FONTMANAGER_H_INCLUDE

#include <string>
#include <map>
#include <stdint.h>

#include "../external/stb_truetype.h"
#include "gli.h"

struct Font
{
  GLuint ftex;
  stbtt_bakedchar cdata[96];

  void size(const std::string& text, float& x, float& y0, float& y1) const;
};

class FontManager
{
public:
  FontManager() {}
  ~FontManager();

  const Font& get(const std::string& f, float sz);
private:
  std::map<std::pair<std::string, float>, Font>::iterator load(const std::string& f, float sz);
  void drop(const std::string& f, float sz);

  std::map<std::pair<std::string, float>, Font> fonts;
};

#endif
