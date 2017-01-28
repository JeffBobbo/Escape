#ifndef UTIL_H_INCLUDE
#define UTIL_H_INCLUDE

#include <string>
#include <algorithm> // std::transform
#include <cctype> // std::toupper
#include <random>

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
extern int64_t frame;
extern int64_t elapsed;
extern int64_t timebase;
extern int64_t last;
extern int64_t delta;
static inline uint64_t tickCount() { return elapsed; }

// math stuff
constexpr double Pi()
{
  return std::atan2(0.0, -1.0);
}

inline double radians(const double degrees)
{
  static const double ratio = Pi() / 180.0;
  return degrees * ratio;
}
inline double degrees(const double radians)
{
  static const double ratio = 180.0 / Pi();
  return radians * ratio;
}

template <typename T> inline T interpolate(const T& a, const T& b, const double& p)
{
  return (b - a) * p + a;
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
  Vec2D(const double u, const double v) : x(u), y(v) {}
  Vec2D(const double d) : x(d), y(d) {}
  Vec2D(Vec2D&& v) : x(v.x), y(v.y) {}

  Vec2D& operator=(const double d)
  {
    x = d;
    y = d;
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
  inline Vec2D normalised() const
  {
    const double length = magnitude();
    return length == 0 ? Vec2D(1.0, 0.0) : *this / length;
  }
  inline double angle() const
  {
    return std::atan2(-y, x);
  }

  double dot(const Vec2D& v) const
  {
    return x*v.x + y*v.y;
  }
  bool isParallel(const Vec2D& v) const
  {
    return x*v.y+ y*v.x == 0.0;
  }

  void rotate(double t)
  {
    const double tcos = std::cos(-t);
    const double tsin = std::sin(-t);
    x = x * tcos - y * tsin;
    y = x * tsin + y * tcos;
  }

  double x;
  double y;
};
#endif
