#ifndef EXIT_H_INCLUDE
#define EXIT_H_INCLUDE

#include "object.h"
#include "trigger.h"
#include <string>

#include "../util.h"

class Exit : public Object, public Actuator
{
public:
  Exit(Vec2D pos, const std::string& n = "");
  virtual ~Exit() {}

  virtual inline Type type() const { return Type::EXIT; }

  inline std::string getNext() const { return name; }
  virtual void actuate() {}
  bool active() const;

private:
  std::string name;
};

#endif
