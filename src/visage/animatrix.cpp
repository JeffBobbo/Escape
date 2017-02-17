#include "animatrix.h"

#include "../gli.h"
#include "../util.h"
#include "../colour.h"

Animatrix::Animatrix()
  : start(0), end(0), loop(0)
  , startColour(0xFFFFFF), endColour(0xFFFFFF)
  , startScaleX(1.0), startScaleY(1.0), endScaleX(1.0), endScaleY(1.0)
  , startAngle(0.0), endAngle(0.0), rotation(0.0)
  , startX(0.0), startY(0.0), endX(0.0), endY(0.0)
  , visible(true)
{
}

void Animatrix::apply() const
{
  if (!isActive())
    return;
  if (!isVisible())
    return;

  double offsetX = 0.0;
  double offsetY = 0.0;
  double angle = 0.0;
  double scalex = 1.0;
  double scaley = 1.0;

  double col[4];
  glGetDoublev(GL_CURRENT_COLOR, col);

  offsetX += startX;
  offsetY += startY;

  if (loop > 0)
  {
    const double p = (tickCount() % (end-start)) / static_cast<double>(end-start);

    if (startColour != endColour)
    {
      RGBA cf = interpolate(fromInt(startColour), fromInt(endColour), p);
      col[0] *= cf.r;
      col[1] *= cf.g;
      col[2] *= cf.b;
      col[3] *= cf.a;
    }

    if (startScaleX != endScaleX)
      scalex *= interpolate(startScaleX, endScaleX, p);
    if (startScaleY != endScaleY)
      scaley *= interpolate(startScaleY, endScaleY, p);
  }
  glTranslated(offsetX, offsetY, 0.0);
  glRotated(angle, 0.0, 0.0, 1.0);
  glScaled(scalex, scaley, 1.0);
  glColor4dv(col);
}
