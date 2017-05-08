#ifndef FONTMANAGER_H_INCLUDE
#define FONTMANAGER_H_INCLUDE

#include <string>
#include <map>
#include <stdint.h>

#include "../external/stb_truetype.h"
#include "gli.h"

struct Font
{
  uint8_t* data;
  double size;
  GLuint ftex;
  stbtt_bakedchar cdate[96];
};

class FontManager
{
public:
  FontManager() {}
  ~FontManager();

  const Font& get(const std::string& f, double sz);
private:
  void load(const std::string& f, double sz);
  void drop(const std::string& f, double sz);

  std::map<std::pair<std::string, double>, Font> fonts;
};

void dropTexture(const std::string& t);
inline void dropTexture(const char* const t)
{
  dropTexture(std::string(t));
}
void dropAllTextures();

void bindTexture(const std::string& t);
inline void bindTexture(const char* const t)
{
  return bindTexture(std::string(t));
}

#endif
