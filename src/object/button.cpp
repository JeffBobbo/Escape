#include "button.h"

#include <sstream>

#include "effect.h"
#include "player.h"
#include "../main.h"
#include "../controls.h"

Button::Button(Vec2D pos, millis_t t, const std::string&& a)
  : Object({0.25, 0.25}, pos), Trigger()
  , last(0), timeout(t)
  , action(a)
  , lastFlash(0)
{
  visage = VisagePolygon::circle(0.1, 16);
  static_cast<VisagePolygon*>(visage)->setColour(0xff7f7fff);
}

void Button::idle()
{
  const Player* const p = level->getPlayer();
  if (p && distance(p) < 1.0 && lastFlash + 1000 < elapsed)
  {
    KeyCode key = bind(controls::Action::USE);
    std::stringstream msg;
    msg << "PRESS " << static_cast<char>(std::toupper(static_cast<char>(key))) << " TO ";
    if (action.length())
      msg << action;
    else
      msg << " USE";

    Vec2D p = position + Vec2D(0.0, 0.5);
    Effect* e = new Effect(p, 1000, new VisageText(msg.str(), "sui_generis.ttf", 12));
    level->insert(SceneGraph::Level::FOREGROUND, e);
    lastFlash = elapsed;
  }
  if (visage && visage->type() == Visage::Type::POLYGON)
  {
    if (on())
      static_cast<VisagePolygon*>(visage)->setColour(0xff0000ff);
    else
      static_cast<VisagePolygon*>(visage)->setColour(0xff7f7fff);
  }
}
