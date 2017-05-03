#include "trigger.h"

void Trigger::link(Actuator* a)
{
  actuator = a;
  actuator->trigger = this;
}

void Actuator::link(Trigger* t)
{
  trigger = t;
  trigger->actuator = this;
}
