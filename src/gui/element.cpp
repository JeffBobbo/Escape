#include "element.h"

#include "../main.h"

void GUIElement::showMenuMain()
{
  if (!root)
  {
    root = new GUIWindow();
    root->setRelative(0.0, 0.0, 1.0, 1.0);
    root->setPosition(0, 0, 0, 0);
    root->setBackgroundColour(0x3f3f3FAF);
  }
  else
  {
    root->removeChildren();
  }

  {
    GUILabel* title = new GUILabel("Shifter");
    title->setRelative(0.5, 0.25, 0.5, 0.25);
    title->setPosition(-20, -10, 20, 10);
    title->setTextColour(0xFF0000FF);
    root->addElement(title);
    GUILabel* play = new GUILabel("Play!");
    play->setRelative(0.5, 0.35, 0.5, 0.35);
    play->setPosition(-20, -10, 20, 10);
    play->setTextColour(0xFFFFFFFF);
    play->registerListener([play](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      int32_t a, b, c, d;
      play->getPosition(a, b, c, d);
      return (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
    }, [play](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      play->setTextColour(0x00FF00FF);
      return false;
    });
    play->registerListener([play](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      int32_t a, b, c, d;
      play->getPosition(a, b, c, d);
      return !(a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
    }, [play](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      play->setTextColour(0xFF0000FF);
      return false;
    });
    play->registerListener([play](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      if (!mouse::left())
        return false;
      int32_t a, b, c, d;
      play->getPosition(a, b, c, d);
      return (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
      }, [](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      delete level;
      level = Level::fromName("prefab0");
      GUIElement::showGameHud();
      if (level == nullptr)
      {
        std::cerr << "Failed to load level" << std::endl;
        glutLeaveMainLoop();
      }
      return true;
    });
    root->addElement(play);
  }
}

void GUIElement::showGameHud()
{
  if (!root)
  {
    root = new GUIWindow();
    root->setRelative(0.0, 0.0, 1.0, 1.0);
    root->setPosition(0, 0, 0, 0);
    // root->setBackgroundColour(0x3f3f3FAF);
  }
  else
  {
    root->removeChildren();
  }
  root->setBackgroundColour(0x00000000);

  {
    GUIImage* image = new GUIImage("img/phase.png");
    image->setRelative(0.0, 0.0, 0.0, 0.0);
    image->setPosition(16, 16, 16+128, 16+16);
    image->setColour(0xFFFFFFFF);
    image->setVisible(false);
    root->addElement(image);
  }
}

GUIElement::GUIElement()
  : x0(0), y0(0), x1(0), y1(0)
  , px0(0.0), py0(0.0), px1(0.0), py1(0.0)
  , visible(true)
  , parent(nullptr)
{
}

void GUIElement::setPosition(int32_t w, int32_t x, int32_t y, int32_t z)
{
  x0 = w;
  x1 = y;
  y0 = x;
  y1 = z;
}
void GUIElement::setRelative(double x0, double y0, double x1, double y1)
{
  px0 = x0;
  py0 = y0;
  px1 = x1;
  py1 = y1;
}
void GUIElement::getPosition(int32_t& w, int32_t& x, int32_t& y, int32_t& z) const
{
  int32_t p = 0, q = 0, r = 0, s = 0;
  if (parent)
  {
    parent->getPosition(p, q, r, s);
    w = p + static_cast<int32_t>(px0 * (r-p) + x0);
    x = q + static_cast<int32_t>(py0 * (s-q) + y0);
    y = p + static_cast<int32_t>(px1 * (r-p) + x1);
    z = q + static_cast<int32_t>(py1 * (s-q) + y1);
  }
  else
  {
    w = static_cast<int32_t>(px0 * screenWidth  + x0);
    x = static_cast<int32_t>(py0 * screenHeight + y0);
    y = static_cast<int32_t>(px1 * screenWidth  + x1);
    z = static_cast<int32_t>(py1 * screenHeight + y1);
  }
}
/*
void GUIElement::getSize(int32_t& w, int32_t& h) const
{
  int32_t p0, q0, p1, q1;
  if (parent)
  {
    int32_t pWidth, pHeight;
    parent->getSize(pWidth, pHeight);
    p0 = pWidth * px0 + x0;
    q0 = pHeight * py0 + y0;
    p1 = pWidth * px1 + x1;
    q1 = pHeight * px1 + y1;
  }
  else
  {
    p0 = screenWidth * px0 + x0;
    q0 = screenHeight * py0 + y0;
    p1 = screenWidth * px1 + x1;
    q1 = screenHeight * px1 + y1;
  }
  w = p1 - p0;
  h = q1 - q0;
}
 */

bool GUIElement::isVisible() const
{
  if (!visible)
    return false;
  return parent ? parent->isVisible() : true;
}

void GUIElement::registerListener(GUIElement::Event e, std::function<bool(void)> f)
{
  callbacks[e] = f;
}

void GUIElement::registerListener(GUIElement::Trigger t, GUIElement::Callback c)
{
  auto p = std::make_pair(t, c);
  events.push_back(p);
}

bool GUIElement::callListener(GUIElement::Event e)
{
  return isListening(e) ? callbacks[e]() : false;
}

bool GUIElement::testListeners(const mouse::MouseState& m)
{
  if (mouse::left())
  {
    int32_t a, b, c, d;
    getPosition(a, b, c, d);
    if (a <= m.x && m.x <= c && b <= m.y && m.y <= d)
      return callListener(GUIElement::Event::ON_CLICK);
  }
  return false;
}

bool GUIElement::testListeners(const mouse::MouseState& ms, const keyboard::KeyboardState& ks)
{
  bool r = false;
  for (auto it : events)
  {
    if (it.first(ms, ks))
      it.second(ms, ks);
  }
  return r;
}

bool GUIElement::onClickLeft(const mouse::MouseState& ms, const keyboard::KeyboardState& ks)
{
  (void)ks;
  if (!mouse::left())
    return false;

  int32_t a, b, c, d;
  getPosition(a, b, c, d);
  return (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
}
bool GUIElement::onClickRight(const mouse::MouseState& ms, const keyboard::KeyboardState& ks)
{
  (void)ks;
  if (!mouse::right())
    return false;

  int32_t a, b, c, d;
  getPosition(a, b, c, d);
  return (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
}
bool GUIElement::onClickMiddle(const mouse::MouseState& ms, const keyboard::KeyboardState& ks)
{
  (void)ks;
  if (!mouse::middle())
    return false;

  int32_t a, b, c, d;
  getPosition(a, b, c, d);
  return (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
}
