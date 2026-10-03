//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 26.03.2021
//


#pragma once

#include <QOpenGLWidget>

// Draws a few colored 2D shapes with OpenGL. The picture stays square and
// centered when the window is resized.
class RenderWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  RenderWidget(QWidget *parent = nullptr);

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

protected:
  void initializeGL() override;
  void paintGL() override;
};
