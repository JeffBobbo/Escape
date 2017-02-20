#ifndef TYPES_H_INCLUDE
#define TYPES_H_INCLUDE

#include <stdint.h>

typedef int16_t phase_t;

#ifdef MILLIS_FIX
struct millis_t
{
  double d;

  millis_t()
  {
  }

  explicit millis_t(double a)
    : d(a)
  {
  }

  millis_t(const millis_t& a)
    : d(a.d)
  {
  }

  inline millis_t& operator=(const millis_t& o)
  {
    d = o.d;
    return *this;
  }

  inline millis_t operator+(const millis_t& o) const
  {
    return millis_t(d + o.d);
  }
  inline millis_t operator-(const millis_t& o) const
  {
    return millis_t(d - o.d);
  }
  inline millis_t operator*(const millis_t& o) const
  {
    return millis_t(d * o.d);
  }
  inline millis_t operator/(const millis_t& o) const
  {
    int32_t x = d;
    int32_t y = o.d;
    return millis_t(x / y);
  }
  inline millis_t operator%(const millis_t& o) const
  {
    return millis_t(static_cast<double>(static_cast<int32_t>(d) % static_cast<int32_t>(o.d)));
  }

  inline operator bool() const { return d; }
  inline bool operator==(const millis_t& o) const { return d == o.d; }
  inline bool operator!=(const millis_t& o) const { return d != o.d; }
  inline bool operator<(const millis_t& o) const { return d < o.d; }
  inline bool operator>(const millis_t& o) const { return d > o.d; }
  inline bool operator<=(const millis_t& o) const { return d <= o.d; }
  inline bool operator>=(const millis_t& o) const { return d >= o.d; }

  inline millis_t& operator+=(const millis_t& o)
  {
    d += o.d;
    return *this;
  }
};
#else
typedef int32_t millis_t;
#endif

#endif
