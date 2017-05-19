#include "keys.h"

#include <cctype>
#include <iostream>

std::string keyCodeToString(const KeyCode code)
{
  if (std::isgraph(static_cast<char>(code)))
    return std::string(1, static_cast<char>(code));

  if (code >= KeyCode::KEY_F1 && code <= KeyCode::KEY_F12)
    return "F" + std::to_string(static_cast<uint16_t>(code) - static_cast<uint16_t>(KeyCode::KEY_F1) + 1);

  switch (code)
  {
    case KeyCode::KEY_BACKSPACE:
      return "Backspace";
    case KeyCode::KEY_TAB:
      return "Tab";
    case KeyCode::KEY_RETURN:
      return "Return";
    case KeyCode::KEY_ESC:
      return "Escape";
    case KeyCode::KEY_SPACE:
      return "Space";

    case KeyCode::KEY_LEFT:
      return "Left Arrow";
    case KeyCode::KEY_UP:
      return "Up Arrow";
    case KeyCode::KEY_RIGHT:
      return "Right Arrow";
    case KeyCode::KEY_DOWN:
      return "Down Arrow";

    case KeyCode::KEY_PAGE_UP:
      return "Page Up";
    case KeyCode::KEY_PAGE_DOWN:
      return "Page Down";
    case KeyCode::KEY_HOME:
      return "Home";
    case KeyCode::KEY_END:
      return "End";
    case KeyCode::KEY_INSERT:
      return "Insert";
    default:
      std::cerr << "Unhandled KeyCode in keyCodeToString(" << static_cast<uint16_t>(code) << ")";
    break;
  }
  return "";
}
