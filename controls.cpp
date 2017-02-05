#include "controls.h"

#include <map>
#include <utility> // std::make_pair

std::map<controls::Action, KeyCode> defaultmap;
std::map<controls::Action, KeyCode> controlmap;

KeyCode controls::bind(const Action a)
{
  auto it = controlmap.find(a);
  if (it == controlmap.end())
  {
    it = defaultmap.find(a);
    if (it != defaultmap.end())
      return it->second;
    exit(1);
  }
  return it->second;
}


void loadDefaults()
{
  defaultmap.insert(std::make_pair(controls::Action::JUMP, KeyCode::KEY_w));
  defaultmap.insert(std::make_pair(controls::Action::CROUCH, KeyCode::KEY_s));
  defaultmap.insert(std::make_pair(controls::Action::MOVE_LEFT, KeyCode::KEY_a));
  defaultmap.insert(std::make_pair(controls::Action::MOVE_RIGHT, KeyCode::KEY_d));
  defaultmap.insert(std::make_pair(controls::Action::WALK_MODIFIER, KeyCode::KEY_q));

  defaultmap.insert(std::make_pair(controls::Action::PHASE_UP, KeyCode::KEY_v));
  defaultmap.insert(std::make_pair(controls::Action::PHASE_DOWN, KeyCode::KEY_c));
  defaultmap.insert(std::make_pair(controls::Action::USE, KeyCode::KEY_e));

  defaultmap.insert(std::make_pair(controls::Action::PAUSE, KeyCode::KEY_p));
  defaultmap.insert(std::make_pair(controls::Action::MUTE_ALL, KeyCode::KEY_m));
}
void loadCustoms()
{
  controlmap.insert(std::make_pair(controls::Action::JUMP, KeyCode::KEY_SPACE));
}


void controls::init()
{
  loadDefaults();
  loadCustoms();
}
