#ifndef EXIT_H_INCLUDE
#define EXIT_H_INCLUDE

#include "object.h"
#include "trigger.h"

#include <string>

class Exit : public Object, public Actuator
{
public:
  Exit(double u, double v, const std::string& n = "");
  virtual ~Exit() {}

  virtual inline Type type() const { return Type::EXIT; }

  inline std::string getNext() const { return name; }
  virtual void actuate() {}
  bool active() const;

private:
  std::string name;
};

#endif
