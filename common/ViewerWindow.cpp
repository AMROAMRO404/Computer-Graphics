//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 26.03.2021
//


#include "ViewerWindow.h"

#include <QFileDialog>
#include <QKeySequence>
#include <QMessageBox>
#include <QPixmap>
#include <QShortcut>
#include <QVBoxLayout>

ViewerWindow::ViewerWindow(QWidget *canvas, const QString &title, QWidget *parent)
  : QWidget(parent), m_Canvas(canvas)
{
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(m_Canvas);

  setWindowTitle(title);

  QShortcut *saveShortcut = new QShortcut(QKeySequence(QKeySequence::Save), this);
  connect(saveShortcut, &QShortcut::activated, this, &ViewerWindow::saveScreenshot);

  QShortcut *quitShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
  connect(quitShortcut, &QShortcut::activated, this, &QWidget::close);
}

void ViewerWindow::saveScreenshot()
{
  const QString path = QFileDialog::getSaveFileName(
      this, tr("Save screenshot"), QStringLiteral("screenshot.png"), tr("PNG image (*.png)"));
  if (path.isEmpty())
    return;

  if (!m_Canvas->grab().save(path))
    QMessageBox::warning(this, tr("Save screenshot"), tr("Could not write %1").arg(path));
}
