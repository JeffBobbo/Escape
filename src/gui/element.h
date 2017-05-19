#ifndef GUIELEMENT_H_INCLUDE
#define GUIELEMENT_H_INCLUDE

#include <stdint.h>
#include <functional>
#include <map>
#include <vector>
#include <utility> // std::pair

#include "../input.h"

class GUIElement
{
public:
  typedef std::function<bool(const mouse::MouseState&, const keyboard::KeyboardState&)> Trigger;
  typedef std::function<bool(const mouse::MouseState&, const keyboard::KeyboardState&)> Callback;

  static void setupRoot();
  static void showMenuMain();
  static void showControlsMenu();
  static void showGameHud();

  GUIElement();
  virtual ~GUIElement() {}

  virtual void draw() const = 0;

  virtual void setPosition(int32_t w, int32_t x, int32_t y, int32_t z);
  virtual void setRelative(double x0, double y0, double x1, double y1);
  virtual void getPosition(int32_t& w, int32_t& x, int32_t& y, int32_t& z) const;
  //virtual void getSize(int32_t& w, int32_t& h) const;
  virtual void setParent(GUIElement* e) { parent = e; }

  bool isVisible() const;
  inline void setVisible(bool v) { visible = v; }

  virtual void registerListener(GUIElement::Trigger t, GUIElement::Callback c);
  virtual bool testListeners(const mouse::MouseState& ms, const keyboard::KeyboardState& ks);

protected:
  int32_t x0, y0, x1, y1;
  double px0, py0, px1, py1;
  bool visible;
  GUIElement* parent;
  std::vector<std::pair<Trigger, Callback> > events;
};

#endif
