#include "controls.h"

#include <map>
#include <utility> // std::make_pair

std::map<controls::Action, KeyCode> defaultmap;
std::map<controls::Action, KeyCode> controlmap;

std::string controls::actionToString(const controls::Action a)
{
  switch (a)
  {
    case controls::Action::MOVE_LEFT:
      return "MOVE_LEFT";
    case controls::Action::MOVE_RIGHT:
      return "MOVE_RIGHT";
    case controls::Action::JUMP:
      return "JUMP";
    case controls::Action::CROUCH:
      return "CROUCH";
    case controls::Action::WALK_MODIFIER:
      return "WALK";
    case controls::Action::USE:
      return "USE";
    case controls::Action::PAUSE:
      return "PAUSE";
    case controls::Action::MUTE_MUSIC:
      return "MUTE_MUSIC";
    case controls::Action::MUTE:
      return "MUTE";
    case controls::Action::NONE:
      return "??";
  }
  return "??";
}
controls::Action controls::actionFromString(const std::string& s)
{
  if (s == "MOVE_LEFT")
    return controls::Action::MOVE_LEFT;
  else if (s == "MOVE_RIGHT")
    return controls::Action::MOVE_RIGHT;
  else if (s == "JUMP")
    return controls::Action::JUMP;
  else if (s == "CROUCH")
    return controls::Action::CROUCH;
  else if (s == "WALK")
    return controls::Action::WALK_MODIFIER;
  else if (s == "USE")
    return controls::Action::USE;
  else if (s == "PAUSE")
    return controls::Action::PAUSE;
  else if (s == "MUTE_MUSIC")
    return controls::Action::MUTE_MUSIC;
  else if (s == "MUTE")
    return controls::Action::MUTE;
  else
    return controls::Action::NONE;
}


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

  defaultmap.insert(std::make_pair(controls::Action::USE, KeyCode::KEY_e));

  defaultmap.insert(std::make_pair(controls::Action::PAUSE, KeyCode::KEY_p));
  defaultmap.insert(std::make_pair(controls::Action::MUTE, KeyCode::KEY_m));
}

#include <fstream>
#include <iostream>
void loadCustoms()
{
  controlmap.clear();

  std::ifstream ifs("controls.txt");
  if (!ifs.good())
    return;
  std::string a;
  int k;
  while (ifs >> a >> k)
    controlmap.insert(
      std::make_pair(controls::actionFromString(a), static_cast<KeyCode>(k)));
  ifs.close();
}

void controls::save()
{
  std::ofstream ofs("controls.txt");
  if (!ofs.good())
    return;
  for (auto it : controlmap)
  {
    ofs << controls::actionToString(it.first) << " " << static_cast<int>(it.second) << std::endl;
  }
  ofs.close();
}

void controls::init()
{
  loadDefaults();
  loadCustoms();
}
