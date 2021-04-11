#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setUsername(QString str){
    ui->label_userName->setText(str);
}
MainWindow::~MainWindow()
{
    delete ui;
}

