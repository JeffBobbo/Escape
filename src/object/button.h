#ifndef BUTTON_H_INCLUDE
#define BUTTON_H_INCLUDE

#include "object.h"
#include "trigger.h"

class Button : public Object, public Trigger
{
public:
  Button(double u, double v, millis_t t, const std::string&& a = "");
  virtual ~Button() {};

  virtual inline Type type() const { return Type::TRIGGER; }
  virtual void idle();

  virtual inline bool on() const
  {
    return timeout == -1 ? last != 0 : elapsed - last < timeout;
  }

  virtual inline void set()
  {
    last = timeout == -1 ? !last : elapsed;
    if (actuator)
      actuator->actuate();
  }

private:
  millis_t last;
  millis_t timeout;
  std::string action;
  millis_t lastFlash;
};

#endif
