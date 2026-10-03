//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 26.03.2021
//


#pragma once

#include <QWidget>

// Top-level window used by both programs. It shows one canvas widget and
// adds the keyboard shortcuts (save a screenshot, quit).
class ViewerWindow : public QWidget
{
  Q_OBJECT

public:
  ViewerWindow(QWidget *canvas, const QString &title, QWidget *parent = nullptr);

private:
  void saveScreenshot();

  QWidget *m_Canvas;
};
