#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>

class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    float angle;
    void updateLogic(void);
public:
    GLWidget(QWidget *parent);

protected:
    void initializeGL(void);
    void resizeGL(int w, int h);
    void paintGL(void);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // GLWIDGET_H
