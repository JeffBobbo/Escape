#ifndef COLOUR_H_INCLUDE
#define COLOUR_H_INCLUDE

struct RGBA
{
  double r, g, b, a;
};

// include alpha channel, even though it doesn't make sense, for conversion purposes
struct HSVA
{
  double h, s, v, a;
};

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

static RGBA rgba(HSVA hsva)
{
  if (hsva.s <= 0.0)
    return {0.0, 0.0, 0.0, hsva.a};
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

#endif
