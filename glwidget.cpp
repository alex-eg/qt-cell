#include "glwidget.hpp"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    setMouseTracking(true);
}

void GLWidget::initializeGL(void)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.07, 0.03, 0.05, 0.0);

    GLfloat w = width();
    GLfloat h = height();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
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
    if (event->buttons() != Qt::LeftButton) return;

    int x = event->x();
    int y = event->y();

    int clsz = g->GetCellsize();

    double dx = g->Getdx();
    double dy = g->Getdy();
#define cellCount 30
    if (x < dx || x > (cellCount * clsz + cellCount + dx)) return;
    if (y < dy || y > (cellCount * clsz + cellCount + dy)) return;
#undef cellCount
    int xcell = (x - dx - 1) / (clsz + 1);
    int ycell = (y - dy - 1) / (clsz + 1);

    emit mouseDown(xcell, ycell);
    emit pauseAutomaton();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton) return;

    int x = event->x();
    int y = event->y();

    int clsz = g->GetCellsize();
    int cellCount = life->getCellCount();
    double dx = g->Getdx();
    double dy = g->Getdy();

    if (x < dx || x > (cellCount * clsz + cellCount + dx)) return;
    if (y < dy || y > (cellCount * clsz + cellCount + dy)) return;

    int xcell = (x - dx - 1) / (clsz + 1);
    int ycell = (y - dy - 1) / (clsz + 1);

    emit mouseMove(xcell, ycell);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) emit startAutomaton();
}


void GLWidget::setAutomaton(Automaton* aut)
{
    life = aut;
}

void GLWidget::setGraphics(Graphics *gr)
{
    g = gr;
}
