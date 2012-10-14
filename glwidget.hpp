#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>

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
protected:
    void initializeGL(void);
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
signals:
    void updateAutomata();
    void randomizeAutomata();
};

#endif // GLWIDGET_H
