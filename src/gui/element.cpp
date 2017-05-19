#include "element.h"

#include <sstream>

#include "../main.h"
#include "../colour.h"
#include "../controls.h"

void GUIElement::setupRoot()
{
  if (!root)
  {
    root = new GUIWindow();
    root->setRelative(0.0, 0.0, 1.0, 1.0);
    root->setPosition(0, 0, 0, 0);
    root->setBackgroundColour(0x3f3f3F00);
  }
  else
  {
    root->removeChildren();
  }
}

void GUIElement::showMenuMain()
{
  setupRoot();

  {
    GUILabel* title = new GUILabel(TITLE, "sui_generis.ttf", 24);
    title->setRelative(0.5, 0.25, 0.5, 0.25);
    title->setTextColour(0xFF0000FF);
    title->setAlignment(GUILabel::Alignment::CENTRE);
    root->addElement(title);

    GUILabel* play = new GUILabel("Play!", "sui_generis.ttf", 16);
    play->setRelative(0.5, 0.35, 0.5, 0.35);
    play->setTextColour(0xFF0000FF);
    play->registerListener([play](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      return true;
    }, [play](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      int32_t a, b, c, d;
      play->getPosition(a, b, c, d);
      if (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d)
        play->setTextColour(0x00FF00FF);
      else
        play->setTextColour(0xFF0000FF);
      return false;
    });
    play->registerListener([play](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      if (keyboard::pressed(KeyCode::KEY_SPACE))
        return true;
      if (!mouse::left())
        return false;
      int32_t a, b, c, d;
      play->getPosition(a, b, c, d);
      return (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
    }, [](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      delete level;
      level = Level::fromName("escape0");
      GUIElement::showGameHud();
      if (level == nullptr)
      {
        std::cerr << "Failed to load level" << std::endl;
        glutLeaveMainLoop();
      }
      return true;
    });
    root->addElement(play);

    GUILabel* controls = new GUILabel("Controls", "sui_generis.ttf", 16);
    controls->setRelative(0.5, 0.45, 0.5, 0.45);
    controls->setTextColour(0xFF0000FF);
    controls->registerListener([controls](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      if (!mouse::left())
        return false;
      int32_t a, b, c, d;
      controls->getPosition(a, b, c, d);
      return (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
    }, [controls](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      showControlsMenu();
      return true;
    });
    controls->registerListener([controls](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      return true;
    }, [controls](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      int32_t a, b, c, d;
      controls->getPosition(a, b, c, d);
      if (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d)
        controls->setTextColour(0x00FF00FF);
      else
        controls->setTextColour(0xFF0000FF);
      return false;
    });
    root->addElement(controls);


    GUILabel* quit = new GUILabel("Quit", "sui_generis.ttf", 16);
    quit->setRelative(0.5, 0.55, 0.5, 0.55);
    quit->setTextColour(0xFF0000FF);
    quit->registerListener([quit](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      if (!mouse::left())
        return false;
      int32_t a, b, c, d;
      quit->getPosition(a, b, c, d);
      return (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
    }, [quit](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      glutLeaveMainLoop();
      return true;
    });
    quit->registerListener([quit](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      return true;
    }, [quit](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      int32_t a, b, c, d;
      quit->getPosition(a, b, c, d);
      if (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d)
        quit->setTextColour(0x00FF00FF);
      else
        quit->setTextColour(0xFF0000FF);
      return false;
    });
    root->addElement(quit);
  }
}

void GUIElement::showControlsMenu()
{
  setupRoot();

  {
    GUILabel* title = new GUILabel("Controls", "sui_generis.ttf", 24);
    title->setRelative(0.5, 0.25, 0.5, 0.25);
    title->setTextColour(0xFF0000FF);
    title->setAlignment(GUILabel::Alignment::CENTRE);
    root->addElement(title);
  }

  int y = 0;
  for (auto bind : controls::allBinds())
  {
    GUILabel* action = new GUILabel(controls::actionToString(bind.first), "sui_generis.ttf", 12);
    action->setRelative(0.25, 0.4, 0.25, 0.4);
    action->setPosition(0, y, 0, y);
    root->addElement(action);
    GUILabel* keycode = new GUILabel(keyCodeToString(bind.second), "sui_generis.ttf", 12);
    keycode->setRelative(0.75, 0.4, 0.75, 0.4);
    keycode->setPosition(0, y, 0, y);
    root->addElement(keycode);
    y += 16;
  }

  {
    GUILabel* back = new GUILabel("Back", "sui_generis.ttf", 16);
    back->setRelative(0.5, 0.8, 0.5, 0.8);
    back->setTextColour(0xFF0000FF);
    back->registerListener([back](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      if (!mouse::left())
        return false;
      int32_t a, b, c, d;
      back->getPosition(a, b, c, d);
      return (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d);
    }, [back](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      showMenuMain();
      return true;
    });
    back->registerListener([back](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ms;
      (void)ks;
      return true;
    }, [back](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) -> bool {
      (void)ks;
      int32_t a, b, c, d;
      back->getPosition(a, b, c, d);
      if (a <= ms.x && ms.x <= c && b <= ms.y && ms.y <= d)
        back->setTextColour(0x00FF00FF);
      else
        back->setTextColour(0xFF0000FF);
      return false;
    });
    root->addElement(back);
  }
}

void GUIElement::showGameHud()
{
  setupRoot();
  root->setBackgroundColour(0x00000000);

  {
    GUIImage* bleed = new GUIImage("img/damage.png");
    bleed->setRelative(0.0, 0.0, 1.0, 1.0);
    bleed->setPosition(0, 0, 0, 0);
    bleed->setColour(0x00000000);
    bleed->registerListener([](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) {
      (void)ms;
      (void)ks;
      return true;
    }, [bleed](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) {
      (void)ms;
      (void)ks;
      if (level && level->getPlayer())
      {
        double frac = level->getPlayer()->getHealthPercentage();
        if (frac == 1.0)
        {
          bleed->setVisible(false);
        }
        else
        {
          bleed->setVisible(true);
          millis_t pulseRate = 500;//(frac < 0.25 ? 400 : (frac < 0.5 ? 600 : 800));//(frac + 0.25) * 1600.0;
          millis_t pulse = (elapsed % pulseRate);
          if (pulse > (pulseRate/2))
            pulse = pulseRate - pulse;
          double p = pulse / (pulseRate / 4.0);
          uint32_t a = static_cast<uint32_t>((1.0 - frac) * 255.0 * p);
          bound(a, 0x0U, 0xFFU);
          bleed->setColour(0xFF000000 | a);
        }
      }
      return false;
    });
    root->addElement(bleed);
  }
  {
    GUILabel* steps = new GUILabel();
    steps->setRelative(0.0, 0.0, 0.0, 0.0);
    steps->setPosition(16, 16, 16+128, 32);
    steps->setTextColour(0xFFFFFFFF);
    steps->setVisible(true);
    steps->registerListener([](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) {
      (void)ms;
      (void)ks;
      return true;
    }, [steps](const mouse::MouseState& ms, const keyboard::KeyboardState& ks) {
      (void)ms;
      (void)ks;
      if (level && level->getPlayer())
      {
        std::stringstream ss;
        ss << "Steps: " << level->getPlayer()->stepCount() << std::endl <<
              "Jumps: " << level->getPlayer()->jumpCount() << std::endl <<
              "Health: " << level->getPlayer()->getHealth();
        steps->setText(ss.str());
      }
      return false;
    });
    root->addElement(steps);
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

void GUIElement::registerListener(GUIElement::Trigger t, GUIElement::Callback c)
{
  auto p = std::make_pair(t, c);
  events.push_back(p);
}

bool GUIElement::testListeners(const mouse::MouseState& ms, const keyboard::KeyboardState& ks)
{
  for (auto it : events)
  {
    if (it.first(ms, ks))
    {
      if (it.second(ms, ks))
        return true;
    }
  }
  return false;
}
