// Tests for the scan-conversion algorithms. Plain C++, no Qt needed:
//   c++ -std=c++17 -I.. RasterizerTest.cpp ../Rasterizer.cpp -o RasterizerTest

#include "Rasterizer.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

namespace
{

using Pixels = std::vector<std::pair<int, int>>;

int failures = 0;

#define CHECK(cond) \
  do { \
    if (!(cond)) { \
      std::cerr << __FILE__ << ":" << __LINE__ << ": CHECK failed: " #cond "\n"; \
      ++failures; \
    } \
  } while (false)

raster::PlotFn collectInto(Pixels &pixels)
{
  return [&pixels](int x, int y) { pixels.emplace_back(x, y); };
}

// A line must start and end on its endpoints and never leave a gap.
void checkConnectedLine(const Pixels &pixels, int x1, int y1, int x2, int y2)
{
  CHECK(!pixels.empty());
  if (pixels.empty())
    return;

  CHECK(pixels.front() == std::make_pair(x1, y1));
  CHECK(pixels.back() == std::make_pair(x2, y2));
  CHECK(static_cast<int>(pixels.size()) == std::max(std::abs(x2 - x1), std::abs(y2 - y1)) + 1);

  for (size_t i = 1; i < pixels.size(); ++i)
  {
    CHECK(std::abs(pixels[i].first - pixels[i - 1].first) <= 1);
    CHECK(std::abs(pixels[i].second - pixels[i - 1].second) <= 1);
  }
}

void testLinesInEveryDirection()
{
  // shallow, steep, horizontal, vertical and diagonal, in both directions
  const int ends[][2] = {{10, 3}, {3, 10}, {-10, 3}, {-3, 10}, {10, -3}, {3, -10},
                         {-10, -3}, {-3, -10}, {10, 0}, {-10, 0}, {0, 10}, {0, -10},
                         {7, 7}, {-7, 7}, {7, -7}, {-7, -7}};

  for (const auto &end : ends)
  {
    const int x1 = 50, y1 = 50;
    const int x2 = x1 + end[0], y2 = y1 + end[1];

    Pixels bresenham;
    raster::lineBresenham(x1, y1, x2, y2, collectInto(bresenham));
    checkConnectedLine(bresenham, x1, y1, x2, y2);

    Pixels dda;
    raster::lineDDA(x1, y1, x2, y2, collectInto(dda));
    checkConnectedLine(dda, x1, y1, x2, y2);
  }
}

void testSinglePointLines()
{
  Pixels bresenham;
  raster::lineBresenham(4, 5, 4, 5, collectInto(bresenham));
  CHECK(bresenham == Pixels({{4, 5}}));

  Pixels dda;
  raster::lineDDA(4, 5, 4, 5, collectInto(dda));
  CHECK(dda == Pixels({{4, 5}}));
}

void testCircle()
{
  const int xc = 100, yc = 80, r = 25;
  Pixels pixels;
  raster::circleMidpoint(xc, yc, r, collectInto(pixels));

  bool right = false, left = false, top = false, bottom = false;
  for (const auto &p : pixels)
  {
    const double distance = std::hypot(p.first - xc, p.second - yc);
    CHECK(std::abs(distance - r) < 1.0);

    right = right || p == std::make_pair(xc + r, yc);
    left = left || p == std::make_pair(xc - r, yc);
    top = top || p == std::make_pair(xc, yc - r);
    bottom = bottom || p == std::make_pair(xc, yc + r);
  }
  CHECK(right && left && top && bottom);

  Pixels point;
  raster::circleMidpoint(3, 4, 0, collectInto(point));
  CHECK(!point.empty() && point.front() == std::make_pair(3, 4));

  Pixels nothing;
  raster::circleMidpoint(3, 4, -1, collectInto(nothing));
  CHECK(nothing.empty());
}

void testArc()
{
  const int xc = 100, yc = 100, r = 40;
  Pixels pixels;
  raster::arc(xc, yc, r, 0, 90, collectInto(pixels));

  CHECK(!pixels.empty());
  if (pixels.empty())
    return;

  // 0 degrees is +x, 90 degrees is +y (down on screen)
  CHECK(pixels.front() == std::make_pair(xc + r, yc));
  CHECK(pixels.back() == std::make_pair(xc, yc + r));

  for (size_t i = 0; i < pixels.size(); ++i)
  {
    CHECK(std::abs(std::hypot(pixels[i].first - xc, pixels[i].second - yc) - r) < 1.0);
    CHECK(pixels[i].first >= xc && pixels[i].second >= yc);
    if (i > 0)
    {
      CHECK(std::abs(pixels[i].first - pixels[i - 1].first) <= 1);
      CHECK(std::abs(pixels[i].second - pixels[i - 1].second) <= 1);
    }
  }

  // reversed angles describe the same arc
  Pixels reversed;
  raster::arc(xc, yc, r, 90, 0, collectInto(reversed));
  CHECK(reversed == pixels);

  Pixels nothing;
  raster::arc(xc, yc, 0, 0, 90, collectInto(nothing));
  CHECK(nothing.empty());
}

}

int main()
{
  testLinesInEveryDirection();
  testSinglePointLines();
  testCircle();
  testArc();

  if (failures != 0)
  {
    std::cerr << failures << " check(s) failed\n";
    return EXIT_FAILURE;
  }
  std::cout << "All rasterizer tests passed\n";
  return EXIT_SUCCESS;
}
