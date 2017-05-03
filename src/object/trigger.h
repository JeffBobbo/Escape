#ifndef TRIGGER_H_INCLUDE
#define TRIGGER_H_INCLUDE

class Actuator;
class Trigger
{
  friend Actuator;
public:
  Trigger() : actuator(nullptr) {}
  virtual ~Trigger() {}

  virtual bool on() const = 0;
  virtual void set() = 0;

  void link(Actuator* a);

  inline bool isLinked() const { return actuator != nullptr; }
protected:
  Actuator* actuator;
};

class Actuator
{
  friend Trigger;
public:
  Actuator() : trigger(nullptr) {}
  virtual ~Actuator() {}

  virtual void actuate() = 0;

  void link(Trigger* t);

  inline bool isLinked() const { return trigger != nullptr; }
protected:
  Trigger* trigger;
};

#endif
