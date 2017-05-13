#ifndef UTIL_H_INCLUDE
#define UTIL_H_INCLUDE

#include <string>
#include <algorithm> // std::transform
#include <cctype> // std::toupper
#include <random>

#include "types.h"

// string stuff
inline void toUpper(std::string& s)
{
  std::transform(s.begin(), s.end(), s.begin(), toupper);
}
inline void toLower(std::string& s)
{
  std::transform(s.begin(), s.end(), s.begin(), tolower);
}

inline std::string commify(const int64_t n)
{
  bool neg = n < 0;
  std::string s = std::to_string(std::abs(n));
  const std::string::size_type len = s.length();
  std::string::size_type pos = (len % 3);
  while (pos < len)
  {
    s.replace(pos, 0, 1, ',');
    pos += 4;
  }
  return neg ? "-" + s : s;
}

// time stuff
extern millis_t elapsed;
extern millis_t last;
extern millis_t delta;
static inline millis_t tickCount() { return elapsed; }

// math stuff
#ifdef __GNUC__
// it seems GCC goes against the standard and allows std::atan2 to work
// as constexpr, so let's use that
constexpr double pi()
{
  return std::atan2(0.0, -1.0);
}
#else
// but use an inline call and static const variable for other systems
inline double pi()
{
  static const double p = std::atan2(0.0, -1.0);
  return p;
}
#endif
constexpr double gravity()
{
  return -9.81;
}


inline double radians(const double degrees)
{
  static const double ratio = pi() / 180.0;
  return degrees * ratio;
}
inline double degrees(const double radians)
{
  static const double ratio = 180.0 / pi();
  return radians * ratio;
}

inline double angularDifference(const double r0, const double r1)
{
  double d = r0 - r1;
  while (d > pi())
    d -= pi() * 2.0;
  while (d < -pi())
    d += pi() * 2.0;
  return d;
}

template <typename T> inline T interpolate(const T& a, const T& b, const double& p)
{
  return static_cast<T>((b - a) * p) + a;
}

template <typename T> inline void bound(T& t, const T& min, const T& max)
{
  if (t < min)
    t = min;
  else if (t > max)
    t = max;
}

void seed(uint64_t s);
inline void seed() { seed(0); }
std::mt19937& getMT();
template <typename T> inline T random(const T min, const T max)
{
  std::uniform_int_distribution<T> dist(min, max);
  return dist(getMT());
}
template <> inline float random<float>(const float min, const float max)
{
  std::uniform_real_distribution<float> dist(min, max);
  return dist(getMT());
}
template <> inline double random<double>(const double min, const double max)
{
  std::uniform_real_distribution<double> dist(min, max);
  return dist(getMT());
}

class Vec2D
{
public:
  Vec2D() : x(0.0), y(0.0) {}
  Vec2D(const double u, const double v) : x(u), y(v) {}
  explicit Vec2D(const double d) : x(d), y(d) {}
  Vec2D(const Vec2D& v) : x(v.x), y(v.y) {}
  Vec2D(Vec2D&& v) : x(v.x), y(v.y) {}

  Vec2D& operator=(const double d)
  {
    x = d;
    y = d;
    return *this;
  }
  Vec2D& operator=(const Vec2D& v)
  {
    x = v.x;
    y = v.y;
    return *this;
  }
  Vec2D& operator=(Vec2D&& v)
  {
    x = v.x;
    y = v.y;
    return *this;
  }
  Vec2D operator+(const Vec2D& v) const
  {
    return Vec2D(x+v.x, y+v.y);
  }
  Vec2D operator-(const Vec2D& v) const
  {
    return Vec2D(x-v.x, y-v.y);
  }
  Vec2D operator-() const
  {
    return Vec2D(-x, -y);
  }
  Vec2D operator*(const double d) const
  {
    return Vec2D(x*d, y*d);
  }
  Vec2D operator/(const double d) const
  {
    return Vec2D(x/d, y/d);
  }

  bool operator==(const Vec2D& v) const
  {
    return x == v.x && y == v.y;
  }
  bool operator!=(const Vec2D& v) const
  {
    return !(*this == v);
  }
  operator bool() const
  {
    return x != 0.0 || y != 0.0;
  }
  bool operator!() const
  {
    return !(*this);
  }
  Vec2D& operator+=(const Vec2D& v)
  {
    x+=v.x;
    y+=v.y;
    return *this;
  }
  Vec2D& operator-=(const Vec2D& v)
  {
    x-=v.x;
    y-=v.y;
    return *this;
  }
  Vec2D& operator*=(const double d)
  {
    x*=d;
    y*=d;
    return *this;
  }
  Vec2D& operator/=(const double d)
  {
    x/=d;
    y/=d;
    return *this;
  }

  inline double magnitudeSquared() const
  {
    return x*x+y*y;
  }
  inline double magnitude() const
  {
    return std::sqrt(magnitudeSquared());
  }
  inline double distanceSquared(const Vec2D& v) const
  {
    return (x-v.x)*(x-v.x) + (y-v.y)*(y-v.y);
  }
  inline double distance(const Vec2D& v) const
  {
    return std::sqrt(distanceSquared(v));
  }
  inline void normalise()
  {
    const double length = magnitude();
    if (length == 0.0)
    {
      x = 1.0;
      y = 0.0;
    }
    else
      *this /= length;
  }
  inline Vec2D normalised() const
  {
    const double length = magnitude();
    return length == 0.0 ? Vec2D(1.0, 0.0) : *this / length;
  }
  inline double angle() const
  {
    return std::atan2(y, x);
  }

  double dot(const Vec2D& v) const
  {
    return x*v.x + y*v.y;
  }
  bool isParallel(const Vec2D& v) const
  {
    return x*v.y+ y*v.x == 0.0;
  }

  void rotate(const double t)
  {
    const double tcos = std::cos(-t);
    const double tsin = std::sin(-t);
    x = x * tcos - y * tsin;
    y = x * tsin + y * tcos;
  }

  Vec2D rotated(const double t) const
  {
    const double tcos = std::cos(-t);
    const double tsin = std::sin(-t);
    return {x * tcos - y * tsin, x * tsin + y * tcos};
  }

  double x;
  double y;
};

#endif
