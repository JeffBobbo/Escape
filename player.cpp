#include "player.h"

#include "main.h"

void Player::move()
  {
  if (keys['w'])
    object->y += 0.5 * (delta / 1000.0);
  if (keys['s'])
    object->y -= 0.5 * (delta / 1000.0);
  if (keys['a'])
    object->x -= 0.5 * (delta / 1000.0);
  if (keys['d'])
    object->x += 0.5 * (delta / 1000.0);
}
