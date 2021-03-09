//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.02.2021
//


#include "RenderWidget.h"
#include <QPainter>
#include<cmath>
RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
  // to be implemeted later
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

 //    painter.setRenderHint(QPainter::Antialiasing, false);
  QColor color(0, 0, 0);
  painter.setPen(color);

  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

  /*for (int x = 100; x < 300; ++x)
  {
    painter.drawPoint(x, x);
  }*/

  //horizental lines
  myDrawLine(250, 350, 292, 350);
  myDrawLine(465, 350, 500, 350);
  myDrawLine(250, 380, 500, 380);

  //vertical lines
  myDrawLine(250, 350, 250, 380);
  myDrawLine(500, 350, 500, 380);


  //horizental lines
  myDrawLine(260, 260, 370, 260);
  myDrawLine(260, 280, 370, 280);

  //vertical lines
  myDrawLine(260, 260, 260, 280);
  myDrawLine(370, 260, 370, 280);


  //horizental lines
  myDrawLine(340, 170, 470, 80);
  //myDrawLine(370, 210, 500, 120);
  myDrawLine(370, 210, 400, 190);
  myDrawLine(455, 156, 500, 120);

  //vertical lines
  myDrawLine(340, 170, 370, 210);
  myDrawLine(470, 80, 500, 120);


  //horizental lines
  myDrawLine(320, 200, 345, 180);
  myDrawLine(340, 225, 365, 205);
  //vertical lines
  myDrawLine(320, 200, 340, 225);

  //horizental lines
  myDrawLine(475, 85,500, 65);
  myDrawLine(495, 110, 520, 90);
  //vertical lines
  myDrawLine(500, 65, 520, 90);

  myDrawCircle(430,175,30,360);
  myDrawCircle(430,175,20,360);
  myDrawArc(380,239, -60,120,50);
  myDrawArc(385,232, -45,55,100);

  myDrawArc(385,232, 130,150,100);

  myDrawArc(380,380, -180,0,90);

  myDrawCircle(380,320,15,360);
}

//REFERENCE: https://stackoverflow.com/questions/10060046/drawing-lines-with-bresenhams-line-algorithm
void RenderWidget::myDrawLine(float x1, float y1, float x2, float y2)
{
  QPainter painter(this);

  //    painter.setRenderHint(QPainter::Antialiasing, false);
  QColor color(0, 0, 0);
  painter.setPen(color);
  QPen pen(Qt::black);
  pen.setWidth(4);
  painter.setPen(pen);
  //float m = (y2 - y1) / (x2 - x1);
  int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
   dx=x2-x1;
   dy=y2-y1;
   dx1=fabs(dx);
   dy1=fabs(dy);
   px=2*dy1-dx1;
   py=2*dx1-dy1;
   if(dy1<=dx1) {
    if(dx>=0) {
     x=x1;
     y=y1;
     xe=x2;
    }
    else {
     x=x2;
     y=y2;
     xe=x1;
    }
    painter.drawPoint(x, y);
    for(i=0;x<xe;i++) {
     x=x+1;
     if(px<0) {
      px=px+2*dy1;
     }
     else {
      if((dx<0 && dy<0) || (dx>0 && dy>0)) {
       y=y+1;
      }
      else {
       y=y-1;
      }
      px=px+2*(dy1-dx1);
     }
     painter.drawPoint(x, y);
    }
   }
   else {
    if(dy>=0) {
     x=x1;
     y=y1;
     ye=y2;
    }
    else {
     x=x2;
     y=y2;
     ye=y1;
    }
    painter.drawPoint(x, y);
    for(i=0;y<ye;i++) {
     y=y+1;
     if(py<=0) {
      py=py+2*dx1;
     }
     else {
      if((dx<0 && dy<0) || (dx>0 && dy>0)) {
       x=x+1;
      }
      else {
       x=x-1;
      }
      py=py+2*(dx1-dy1);
     }
     painter.drawPoint(x, y);
    }
   }
}

void RenderWidget::myDrawCircle(float Xc, float Yc, float r, float angle)
{
    QPainter painter(this);

    //    painter.setRenderHint(QPainter::Antialiasing, false);
    QColor color(0, 0, 0);
    painter.setPen(color);
    QPen pen(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);
    float theta = 0;
    float x, y;
    while (theta < angle){
        x = Xc + r*cos((theta*3.14)/180);
        y = Yc + r*sin((theta*3.14)/180);
        painter.drawPoint(x, y);
        theta+=0.1;
    }

}

void RenderWidget::myDrawArc(float Xc, float Yc, float t1, float t2, float r){
    QPainter painter(this);

    //    painter.setRenderHint(QPainter::Antialiasing, false);
    QColor color(0, 0, 0);
    painter.setPen(color);
    QPen pen(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);
    float theta = t1;
    float x, y;
    while (theta < t2){
        x = Xc + r*cos((theta*3.14)/180);
        y = Yc + r*sin((theta*3.14)/180);
        painter.drawPoint(x, y);
        theta+=(1/r);
    }

}
