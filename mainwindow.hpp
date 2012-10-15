#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ltimer.hpp"
#include "automaton.hpp"
#include "graphics.hpp"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;
    LTimer *timer;
    Automaton *life;
    Graphics *graphics;
};

#endif // MAINWINDOW_H
