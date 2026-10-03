//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.02.2021
//


#include "Rasterizer.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace raster
{

namespace
{
const double kPi = 3.14159265358979323846;

int roundToInt(double v)
{
  return static_cast<int>(std::lround(v));
}
}

void lineDDA(double x1, double y1, double x2, double y2, const PlotFn &plot)
{
  const double dx = x2 - x1;
  const double dy = y2 - y1;

  // one step per pixel along the longer axis
  const int steps = roundToInt(std::max(std::abs(dx), std::abs(dy)));
  if (steps == 0)
  {
    plot(roundToInt(x1), roundToInt(y1));
    return;
  }

  for (int i = 0; i <= steps; ++i)
  {
    const double t = static_cast<double>(i) / steps;
    plot(roundToInt(x1 + t * dx), roundToInt(y1 + t * dy));
  }
}

void lineBresenham(int x1, int y1, int x2, int y2, const PlotFn &plot)
{
  const int dx = std::abs(x2 - x1);
  const int dy = -std::abs(y2 - y1);
  const int sx = x1 < x2 ? 1 : -1;
  const int sy = y1 < y2 ? 1 : -1;
  int err = dx + dy;

  while (true)
  {
    plot(x1, y1);
    if (x1 == x2 && y1 == y2)
      break;

    const int e2 = 2 * err;
    if (e2 >= dy)
    {
      err += dy;
      x1 += sx;
    }
    if (e2 <= dx)
    {
      err += dx;
      y1 += sy;
    }
  }
}

void circleMidpoint(int xc, int yc, int r, const PlotFn &plot)
{
  if (r < 0)
    return;

  int x = 0;
  int y = r;
  int p = 1 - r;

  while (x <= y)
  {
    // one computed point gives eight by symmetry
    plot(xc + x, yc + y);
    plot(xc - x, yc + y);
    plot(xc + x, yc - y);
    plot(xc - x, yc - y);
    plot(xc + y, yc + x);
    plot(xc - y, yc + x);
    plot(xc + y, yc - x);
    plot(xc - y, yc - x);

    ++x;
    if (p < 0)
    {
      p += 2 * x + 1;
    }
    else
    {
      --y;
      p += 2 * (x - y) + 1;
    }
  }
}

void arc(double xc, double yc, double r, double startDeg, double endDeg, const PlotFn &plot)
{
  if (r <= 0)
    return;
  if (endDeg < startDeg)
    std::swap(startDeg, endDeg);

  const double start = startDeg * kPi / 180.0;
  const double sweep = (endDeg - startDeg) * kPi / 180.0;

  // an angular step of 1/r radians moves about one pixel along the arc
  const int steps = std::max(1, static_cast<int>(std::ceil(sweep * r)));
  for (int i = 0; i <= steps; ++i)
  {
    const double theta = start + sweep * i / steps;
    plot(roundToInt(xc + r * std::cos(theta)), roundToInt(yc + r * std::sin(theta)));
  }
}

}
