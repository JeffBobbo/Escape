#ifndef GUIWINDOW_H_INCLUDE
#define GUIWINDOW_H_INCLUDE

#include "element.h"
#include <vector>

class GUIWindow : public GUIElement
{
public:
  GUIWindow();
  virtual ~GUIWindow()
  {
    for (const GUIElement* e : elements)
      delete e;
  }

  virtual void draw() const;

  void setBackgroundColour(const uint32_t& c);

  void addElement(GUIElement* e) { elements.push_back(e); e->setParent(this); }

private:
  double col[4];
  std::vector<GUIElement*> elements;
};

#endif
