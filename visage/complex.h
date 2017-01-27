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

  inline void add(Visage* const v) { visages.push_back(v); }

  virtual void draw()
  {
    for (Visage* const v : visages)
    {
      v->draw();
    }
  }

private:
  std::vector<Visage* > visages;
};

#endif
