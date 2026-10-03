//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.04.2018


#include "RenderWidget.h"
#include "ViewerWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  ViewerWindow viewer(new RenderWidget, QObject::tr("2D Graphics: Drawing Elementary Shapes"));

  viewer.show();

  return app.exec();
}
