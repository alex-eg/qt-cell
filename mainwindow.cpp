#include "mainwindow.hpp"
#include "ui_mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new LTimer(this);
    timer->start(10);

    setFixedSize(800,600);
    ui->setupUi(this);

    life = new Automaton(40,
                         40,
                         "23/3",
                         this);

    graphics = new Graphics(ui->glView->width(),
                            ui->glView->height(),
                            this);

    connect(ui->pushButton,SIGNAL(clicked()),
            this->life, SLOT(Randomize()));

    connect(ui->spinBox, SIGNAL(valueChanged(int)),
            this->life, SLOT(ChangeSpeed(int)));

    connect(timer,SIGNAL(timeout()),
            this->life,SLOT(Update()));

    connect(ui->pushButton_2,SIGNAL(clicked()),
            this->life, SLOT(Clear()));

    connect(this->life,SIGNAL(updated()),
            ui->glView,SLOT(updateGL()));

    connect(ui->glView, SIGNAL(mouseDown(int, int)),
            this->life,SLOT(MouseDown(int, int)));

    connect(ui->glView, SIGNAL(mouseMove(int, int)),
            this->life, SLOT(MouseMove(int, int)));

    connect(ui->glView, SIGNAL(pauseAutomaton()),
            this->life, SLOT(stop()));

    connect(ui->glView, SIGNAL(startAutomaton()),
            this->life, SLOT(start()));

    ui->glView->setAutomaton(life);
    ui->glView->setGraphics(graphics);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space: {
        life->Update();
        break;
    }
    case Qt::Key_R: {
        life->Randomize();
        break;
    }
    default: break;
    }
}
