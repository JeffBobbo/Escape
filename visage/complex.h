#ifndef COMPLEX_H_INCLUDE
#define COMPLEX_H_INCLUDE

#include "visage.h"

#include <vector>

class VisageComplex : public Visage
{
public:
  VisageComplex() {}
  virtual ~VisageComplex()
  {
    for (Visage* v : visages)
      delete v;
  }

  virtual inline Type type() const { return Type::COMPLEX; }

  inline void add(Visage* const v) { visages.push_back(v); }

  virtual void draw()
  {
    for (Visage* const v : visages)
    {
      glPushMatrix();
      v->draw();
      glPopMatrix();
    }
  }

private:
  std::vector<Visage* > visages;
};

#endif
