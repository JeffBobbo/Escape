#ifndef VISAGE_H_INCLUDE
#define VISAGE_H_INCLUDE

#include <vector>

#include "animatrix.h"

namespace rapidjson
{
  class Document;
}
class Visage
{
public:
  enum class Type
  {
    POLYGON = 0,
    COMPLEX,
    PARTICLE,
    TEXTURE
  };

  Visage() {}
  virtual ~Visage()
  {
    for (Animatrix* a : animatrices)
      delete a;
  }

  virtual Type type() const = 0;
  //virtual void fromJSON(const rapidjson::Document& doc) = 0;

  virtual void draw()
  {
    for (const Animatrix* const ani : animatrices)
      ani->apply();
  };
  virtual void addAnimatrix(Animatrix* const a) { animatrices.push_back(a); }


  //static void loadVisages();
  //static Visage* getVisage(const std::string& name);
protected:
  std::vector<Animatrix* > animatrices;
};

#endif
