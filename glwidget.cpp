#include "glwidget.hpp"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    setMouseTracking(true);
    angle = 0;
}

void GLWidget::updateLogic(void)
{
    angle += 0.5;
    if (angle == 360) angle = 0;
}

void GLWidget::initializeGL(void)
{
    glClearColor(0.07, 0.03, 0.05, 0.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.375, 0.375, 0.0);
}

void GLWidget::paintGL(void)
{
    updateLogic();
    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glClearColor(0.07, 0.03, 0.05, 0.0);
    glBegin(GL_POLYGON);
    glVertex2d(100,100);
    glVertex2d(400,100);
    glVertex2d(100,400);
    glEnd();
    glPopMatrix();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void GLWidget::keyPressEvent(QKeyEvent *event)
{

}
