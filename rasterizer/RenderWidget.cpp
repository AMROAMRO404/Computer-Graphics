//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.02.2021
//


#include "RenderWidget.h"
#include "Rasterizer.h"

#include <QPainter>
#include <QPen>
#include <QRectF>

#include <cmath>

namespace
{

struct Line { double x1, y1, x2, y2; };
struct Circle { double xc, yc, r; };
struct Arc { double xc, yc, r, startDeg, endDeg; };

// The microscope, in scene coordinates (y grows downwards).

// drawn with Bresenham
const Line kBresenhamLines[] = {
  // base feet
  {250, 350, 292, 350},
  {465, 350, 500, 350},
  {250, 380, 500, 380},
  // stage
  {260, 260, 370, 260},
  {260, 280, 370, 280},
};

// drawn with DDA
const Line kDdaLines[] = {
  // base feet
  {250, 350, 250, 380},
  {500, 350, 500, 380},
  // stage
  {260, 260, 260, 280},
  {370, 260, 370, 280},
  // tube
  {340, 170, 470, 80},
  {370, 210, 400, 190},
  {455, 156, 500, 120},
  {340, 170, 370, 210},
  {470, 80, 500, 120},
  // objective lens
  {320, 200, 345, 180},
  {340, 225, 365, 205},
  {320, 200, 340, 225},
  // eyepiece
  {475, 85, 500, 65},
  {495, 110, 520, 90},
  {500, 65, 520, 90},
};

const Circle kCircles[] = {
  // focus knob
  {430, 175, 30},
  {430, 175, 20},
  // base knob
  {380, 320, 15},
};

const Arc kArcs[] = {
  // arm
  {380, 239, 50, -60, 120},
  {385, 232, 100, -45, 55},
  {385, 232, 100, 130, 150},
  // base dome
  {380, 380, 90, -180, 0},
};

// part of the scene that has to stay visible: the drawing plus a margin
const QRectF kSceneBounds(230, 45, 310, 355);

const double kLineWidth = 4;
const double kCurveWidth = 3;

int roundToInt(double v)
{
  return static_cast<int>(std::lround(v));
}

}

RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
}

QSize RenderWidget::minimumSizeHint() const
{
  return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const
{
  return QSize(700, 700);
}

void RenderWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.setPen(Qt::black);
  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

  // uniform scale that fits the scene in the widget, centered
  const double scale = qMin(width() / kSceneBounds.width(), height() / kSceneBounds.height());
  const double offsetX = (width() - kSceneBounds.width() * scale) / 2 - kSceneBounds.left() * scale;
  const double offsetY = (height() - kSceneBounds.height() * scale) / 2 - kSceneBounds.top() * scale;

  const auto toX = [=](double x) { return x * scale + offsetX; };
  const auto toY = [=](double y) { return y * scale + offsetY; };

  const auto setPenWidth = [&](double sceneWidth) {
    QPen pen(Qt::black);
    pen.setWidth(qMax(1, roundToInt(sceneWidth * scale)));
    painter.setPen(pen);
  };

  const raster::PlotFn plot = [&painter](int x, int y) { painter.drawPoint(x, y); };

  setPenWidth(kLineWidth);
  for (const Line &l : kBresenhamLines)
  {
    raster::lineBresenham(roundToInt(toX(l.x1)), roundToInt(toY(l.y1)),
                          roundToInt(toX(l.x2)), roundToInt(toY(l.y2)), plot);
  }
  for (const Line &l : kDdaLines)
  {
    raster::lineDDA(toX(l.x1), toY(l.y1), toX(l.x2), toY(l.y2), plot);
  }

  setPenWidth(kCurveWidth);
  for (const Circle &c : kCircles)
  {
    raster::circleMidpoint(roundToInt(toX(c.xc)), roundToInt(toY(c.yc)), roundToInt(c.r * scale), plot);
  }
  for (const Arc &a : kArcs)
  {
    raster::arc(toX(a.xc), toY(a.yc), a.r * scale, a.startDeg, a.endDeg, plot);
  }
}
