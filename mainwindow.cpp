#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(800,600);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
