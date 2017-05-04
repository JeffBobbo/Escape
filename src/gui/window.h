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
    for (auto it : elements)
      delete it;
  }

  virtual void draw() const;

  void setBackgroundColour(const uint32_t& c);

  void addElement(GUIElement* e) { elements.push_back(e); e->setParent(this); }
  void removeChildren()
  {
    for (auto it : elements)
      delete it;
    elements.clear();
  }

  virtual bool testListeners(const mouse::MouseState& ms, const keyboard::KeyboardState& ks);

private:
  double col[4];
  std::vector<GUIElement*> elements;
};

#endif
