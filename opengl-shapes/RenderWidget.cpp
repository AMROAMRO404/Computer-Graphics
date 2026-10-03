//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 26.03.2021
//


#include "RenderWidget.h"

#include <initializer_list>

namespace
{

// side of the square world window, in world units
const double kWorldSize = 800.0;

struct Color { float r, g, b; };
struct Vertex { float x, y; Color color; };

const Color kRed    = {1, 0, 0};
const Color kGreen  = {0, 1, 0};
const Color kBlue   = {0, 0, 1};
const Color kYellow = {1, 1, 0};
const Color kWhite  = {1, 1, 1};
const Color kDark   = {0.1f, 0.1f, 0.1f};

// OpenGL blends the vertex colors across the shape
void drawShape(GLenum mode, std::initializer_list<Vertex> vertices)
{
  glBegin(mode);
  for (const Vertex &v : vertices)
  {
    glColor3f(v.color.r, v.color.g, v.color.b);
    glVertex2f(v.x, v.y);
  }
  glEnd();
}

}

RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

QSize RenderWidget::minimumSizeHint() const
{
  return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const
{
  return QSize(800, 800);
}

void RenderWidget::initializeGL()
{
  glClearColor(0.9f, 0.9f, 0.7f, 1.0f);
}

void RenderWidget::paintGL()
{
  // Largest centered square, in physical pixels. Set here rather than in
  // resizeGL() because QOpenGLWidget resets the viewport before paintGL().
  const qreal pixelRatio = devicePixelRatioF();
  const int w = static_cast<int>(width() * pixelRatio);
  const int h = static_cast<int>(height() * pixelRatio);
  const int side = qMin(w, h);
  glViewport((w - side) / 2, (h - side) / 2, side, side);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, kWorldSize, 0.0, kWorldSize, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClear(GL_COLOR_BUFFER_BIT);

  // top right: red/green/blue triangle
  drawShape(GL_TRIANGLES, {
    {600, 750, kGreen},
    {400, 500, kRed},
    {800, 500, kBlue},
  });

  // top left: gradient rectangle
  drawShape(GL_POLYGON, {
    {0,   750, kDark},
    {370, 750, kWhite},
    {370, 300, kDark},
    {0,   300, kWhite},
  });

  // bottom left: yellow triangle
  drawShape(GL_TRIANGLES, {
    {100, 450, kYellow},
    {100, 120, kYellow},
    {350, 120, kYellow},
  });

  // bottom right: blue pentagon
  drawShape(GL_POLYGON, {
    {500, 100, kBlue},
    {750, 100, kBlue},
    {800, 250, kBlue},
    {625, 380, kBlue},
    {450, 250, kBlue},
  });

  // inside the pentagon: triangle fading from a red center to green corners
  drawShape(GL_TRIANGLE_FAN, {
    {620, 215, kRed},
    {550, 150, kGreen},
    {700, 150, kGreen},
    {620, 300, kGreen},
    {550, 150, kGreen},
  });

  glFlush();
}
