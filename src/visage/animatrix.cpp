#include "animatrix.h"

#include "../gli.h"
#include "../util.h"
#include "../colour.h"

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

  if (loop != 0)
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
  glTranslatef(offsetX, offsetY, 0.0);
  glRotatef(angle, 0.0, 0.0, 1.0);
  glScalef(scalex, scaley, 1.0);
  glColor4dv(col);
}