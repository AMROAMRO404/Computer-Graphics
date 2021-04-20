//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 26.03.2021
//


#include "RenderWidget.h"
#include <glut.h>
#include <QPainter>

RenderWidget::RenderWidget(QWidget *parent) : QGLWidget(parent)
{

}


RenderWidget::~RenderWidget()
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
    glClearColor(0.9, 0.9, 0.7, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
}


void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // top right
    glBegin(GL_TRIANGLES);
      glColor3f(0, 1, 0);   // green
      glVertex2f(600, 750);
      glColor3f(1, 0, 0.0);   // red
      glVertex2f(400, 500);
	  glColor3f(0, 0, 1);   // blue
      glVertex2f(800, 500);
    glEnd();

    // top left
    glBegin(GL_POLYGON);
        glColor3f(0.1, 0.1, 0.1);
        glVertex2f(0, 750);
        glColor3f(1, 1, 1);
        glVertex2f(370, 750);
        glColor3f(0.1, 0.1, 0.1);
        glVertex2f(370, 300);
        glColor3f(1, 1, 1);
        glVertex2f(0, 300);
    glEnd();

    // down left
    glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 0);   // yellow
        glVertex2f(100, 450);
        glVertex2f(100, 120);
        glVertex2f(350, 120);           
    glEnd();

    // down rigth
    glBegin(GL_POLYGON);
        glColor3f(0, 0, 1);   // blue
        glVertex2f(500, 100);
        glVertex2f(750, 100);
        glVertex2f(800, 250);
        glVertex2f(625, 380);
        glVertex2f(450, 250);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0, 1, 0); //green 
        glVertex2f(550, 150);
        glColor3f(0, 1, 0); //green 
        glVertex2f(700, 150);
        glColor3f(1, 0, 0); //red same point for the three tringles 
        glVertex2f(620, 215);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0, 1, 0); //green 
        glVertex2f(550, 150);
        glColor3f(0, 1, 0); //green  
        glVertex2f(620, 300);
        glColor3f(1, 0, 0); //red same point for the three tringles 
        glVertex2f(620, 215);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0, 1, 0); //green  
        glVertex2f(700, 150);
        glColor3f(0, 1, 0); //green  
        glVertex2f(620, 300);
        glColor3f(1, 0, 0); //red same point for the three tringles 
        glVertex2f(620, 215);
    glEnd();

    glFlush();
}


void RenderWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

//    glViewport(0, 0, width, height);
}


