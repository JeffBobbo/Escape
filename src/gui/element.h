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

  static void showMenuMain();
  static void showGameHud();

  enum class Event
  {
    // MOUSE_IN,
    // MOUSE_OUT,
    // MOUSE_SCROLL,
    ON_CLICK
  };
  GUIElement();
  virtual ~GUIElement() {}

  virtual void draw() const = 0;

  virtual void setPosition(int32_t w, int32_t x, int32_t y, int32_t z);
  virtual void setRelative(double x0, double y0, double x1, double y1);
  virtual void getPosition(int32_t& w, int32_t& x, int32_t& y, int32_t& z) const;
  //virtual void getSize(int32_t& w, int32_t& h) const;
  virtual void setParent(GUIElement* e) { parent = e; }

  virtual void registerListener(GUIElement::Event e, std::function<bool(void)> f);
  virtual void registerListener(GUIElement::Trigger t, GUIElement::Callback c);
  virtual inline bool isListening(GUIElement::Event e) { return callbacks.find(e) != callbacks.end(); }
  virtual bool callListener(GUIElement::Event e);
  virtual bool testListeners(const mouse::MouseState& m);
  virtual bool testListeners(const mouse::MouseState& ms, const keyboard::KeyboardState& ks);

  bool onClickLeft(const mouse::MouseState& ms, const keyboard::KeyboardState& ks);
  bool onClickRight(const mouse::MouseState& ms, const keyboard::KeyboardState& ks);
  bool onClickMiddle(const mouse::MouseState& ms, const keyboard::KeyboardState& ks);
protected:
  int32_t x0, y0, x1, y1;
  double px0, py0, px1, py1;
  GUIElement* parent;
  std::map<GUIElement::Event, std::function<bool(void)> > callbacks;
  std::vector<std::pair<Trigger, Callback> > events;
};

#endif
