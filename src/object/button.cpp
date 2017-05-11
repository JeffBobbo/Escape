#include "button.h"

#include <sstream>

#include "effect.h"
#include "player.h"
#include "../main.h"
#include "../controls.h"

Button::Button(double u, double v, millis_t t, const std::string&& a)
  : Object(0.25, 0.25, u, v), Trigger()
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
    msg << "PRESS " << std::toupper(static_cast<char>(key)) << " TO ";
    if (action.length())
      msg << action;
    else
      msg << " USE";

    Effect* e = new Effect(position.x, position.y+0.5, 1000, new VisageText(msg.str(), "sui_generis.ttf", 12));
    level->insert(SceneGraph::Level::FOREGROUND, e);
    lastFlash = elapsed;
  }
  if (on())
    static_cast<VisagePolygon*>(visage)->setColour(0xff0000ff);
  else
    static_cast<VisagePolygon*>(visage)->setColour(0xff7f7fff);
}
