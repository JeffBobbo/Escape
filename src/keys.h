#ifndef KEYCODES_H_INCLUDE
#define KEYCODES_H_INCLUDE

#include <stdint.h>
#include "gli.h"

enum class KeyCode : uint16_t
{
  KEY_BACKSPACE = '\b',
  KEY_TAB = '\t',
  KEY_RETURN = '\r',
  KEY_ESC = 27,
  KEY_SPACE = ' ',
  KEY_EXCLAMATION,
  KEY_QUOTE,
  KEY_HASH,
  KEY_DOLLAR,
  KEY_PERCENT,
  KEY_AMPERSAND,
  KEY_SINGLE_QUOTE,
  KEY_PARENTHESIS_LEFT,
  KEY_PARENTHESIS_RIGHT,
  KEY_ASTERISK,
  KEY_ADDITION,
  KEY_COMMA,
  KEY_SUBTRACTION,
  KEY_PERIOD,
  KEY_SLASH_FOWARD,

  // numbers
  KEY_ZERO = '0',
  KEY_ONE,
  KEY_TWO,
  KEY_THREE,
  KEY_FOUR,
  KEY_FIVE,
  KEY_SIX,
  KEY_SEVEN,
  KEY_EIGHT,
  KEY_NINE,

  KEY_COLON,
  KEY_SEMICOLON,
  KEY_LESS_THAN,
  KEY_EQUALS,
  KEY_GREATER_THAN,
  KEY_QUESTION,
  KEY_AT,

  // A-Z
  KEY_A = 'A',
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,

  KEY_a = 'a',
  KEY_b,
  KEY_c,
  KEY_d,
  KEY_e,
  KEY_f,
  KEY_g,
  KEY_h,
  KEY_i,
  KEY_j,
  KEY_k,
  KEY_l,
  KEY_m,
  KEY_n,
  KEY_o,
  KEY_p,
  KEY_q,
  KEY_r,
  KEY_s,
  KEY_t,
  KEY_u,
  KEY_v,
  KEY_w,
  KEY_x,
  KEY_y,
  KEY_z,

  KEY_TILDE = '~',

  // begin special keys -- starting at 256, so they're out of ASCII range
  KEY_F1 = 256,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
  KEY_LEFT,
  KEY_UP,
  KEY_RIGHT,
  KEY_DOWN,

  KEY_PAGE_UP,
  KEY_PAGE_DOWN,
  KEY_HOME,
  KEY_END,
  KEY_INSERT
};

enum class KeyModifier
{
  SHIFT = GLUT_ACTIVE_SHIFT,
  CTRL  = GLUT_ACTIVE_CTRL,
  ALT   = GLUT_ACTIVE_ALT
};

std::string keyCodeToString(const KeyCode code);

#endif
