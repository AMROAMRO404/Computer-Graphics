//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.04.2018
//


#pragma once

#include <QWidget>

// Draws a microscope pixel by pixel with the algorithms in Rasterizer.h.
// The drawing is scaled and centered to fit the widget.
class RenderWidget : public QWidget
{
  Q_OBJECT

public:
  RenderWidget(QWidget *parent = nullptr);

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

protected:
  void paintEvent(QPaintEvent *event) override;
};
