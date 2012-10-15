#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

#include "graphics.hpp"
#include "automaton.hpp"

class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    Graphics *g;
    Automaton *life;
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void setAutomaton(Automaton* aut);
    void setGraphics(Graphics* gr);
protected:
    void initializeGL(void);
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void updateAutomata();
    void randomizeAutomata();
    void mouseDown(int,int);
    void mouseMove(int,int);
    void pauseAutomaton();
    void startAutomaton();
};

#endif // GLWIDGET_H
