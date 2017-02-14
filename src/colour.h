#ifndef COLOUR_H_INCLUDE
#define COLOUR_H_INCLUDE

#include <stdint.h>

typedef uint32_t RGBA_t;

struct RGBA
{
  double r, g, b, a;
};

// include alpha channel, even though it doesn't make sense, for conversion purposes
struct HSVA
{
  double h, s, v, a;
};

// algorithm, with some slight modifications, from: http://stackoverflow.com/a/6930407/5187801
static HSVA hsva(RGBA rgba)
{
  HSVA out;
  out.a = rgba.a;
  double min, max, delta;
  min = rgba.r < rgba.g ? rgba.r : rgba.g;
  min = min < rgba.b ? min : rgba.b;

  max = rgba.r > rgba.g ? rgba.r : rgba.g;
  max = max > rgba.b ? max : rgba.b;

  out.v = max;
  delta = max - min;
  if (delta < 0.00001)
  {
    out.s = 0.0;
    out.h = 0.0;
    return out;
  }

  if (max > 0.0)
  {
    out.s = delta / max;
  }
  else
  {
    out.s = 0.0;
    out.h = 0.0;
    return out;
  }
  if (rgba.r >= max)
    out.h = (rgba.g - rgba.b) / delta;
  else if (rgba.g >= max)
    out.h = 2.0 + (rgba.b - rgba.r) / delta;
  else
    out.h = 4.0 + (rgba.r - rgba.g) / delta;
  out.h *= 60.0;

  if (out.h < 0.0)
    out.h += 360.0;
  return out;
}

// algorithm, with some slight modifications, from: http://stackoverflow.com/a/6930407/5187801
static RGBA rgba(HSVA hsva)
{
  if (hsva.s <= 0.0)
    return {hsva.v, hsva.v, hsva.v, hsva.a};
  double hh = hsva.h;
  while (hh >= 360.0)
    hh -= 360.0;
  while (hh < 0.0)
    hh += 360.0;
  hh /= 60.0;
  int i = hh;
  double ff = hh - i;
  double p = hsva.v * (1.0 - hsva.s);
  double q = hsva.v * (1.0 - (hsva.s * ff));
  double t = hsva.v * (1.0 - (hsva.s * (1.0 - ff)));

  switch (i)
  {
    case 0:
      return {hsva.v, t, p, hsva.a};
    case 1:
      return {q, hsva.v, p, hsva.a};
    case 2:
      return {p, hsva.v, t, hsva.a};
    case 3:
      return {p, q, hsva.v, hsva.a};
    case 4:
      return {t, p, hsva.v, hsva.a};
    case 5:
      return {hsva.v, p, q, hsva.a};
  }
  return {0.0, 0.0, 0.0, hsva.a};
}

static inline RGBA fromInt(RGBA_t col)
{
  return {
    ((col >> 24 & 255) / 255.0),
    ((col >> 16 & 255) / 255.0),
    ((col >>  8 & 255) / 255.0),
    ((col       & 255) / 255.0)
  };
}

static inline RGBA_t toInt(const RGBA& col)
{
  return
    (static_cast<RGBA_t>(col.r*255.0) & 255) << 24 |
    (static_cast<RGBA_t>(col.g*255.0) & 255) << 16 |
    (static_cast<RGBA_t>(col.b*255.0) & 255) <<  8 |
    (static_cast<RGBA_t>(col.a*255.0) & 255);
}


static inline RGBA interpolate(const RGBA& c0, const RGBA& c1, double p)
{
  // convert to HSV colourspace
  HSVA h0 = hsva(c0);
  HSVA h1 = hsva(c1);
  return rgba({
    interpolate(h0.h, h1.h, p),
    interpolate(h0.s, h1.s, p),
    interpolate(h0.v, h1.v, p),
    interpolate(h0.a, h1.a, p),
  });
}

#endif
