#ifndef TRIGGER_H_INCLUDE
#define TRIGGER_H_INCLUDE

class Actuator;

class Trigger
{
public:
  Trigger() : actuator(nullptr) {}
  virtual ~Trigger() {}

  virtual bool on() const = 0;
  virtual void set() = 0;

  virtual void link(Actuator* const a)
  {
    actuator = const_cast<Actuator*>(a);
    actuator->trigger = this;
  }

private:
  Actuator* actuator;
};

class Actuator
{
public:
  Actuator() : trigger(nullptr) {}
  virtual ~Actuator() {}

  virtual void actuate() = 0;

  virtual void link(const Trigger* const t)
  {
    trigger = const_cast<Trigger*>(t);
    trigger->actuator = this;
  }

private:
  Trigger* trigger;
};

#endif
