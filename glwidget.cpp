#include "glwidget.hpp"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    setMouseTracking(true);

}

GLWidget::~GLWidget()
{
    delete g;
}

void GLWidget::initializeGL(void)
{
    g = new Graphics(width(), height());

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.07, 0.03, 0.05, 0.0);

    GLfloat w = width();
    GLfloat h = height();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.375, 0.375, 0.0);

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.375, 0.375, 0.0);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    if (life) g->Draw(*life);
    glPopMatrix();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void GLWidget::setAutomaton(Automaton* aut)
{
    life=aut;
}
