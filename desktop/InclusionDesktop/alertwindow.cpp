#include "alertwindow.h"
#include "ui_alertwindow.h"

AlertWindow::AlertWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlertWindow)
{
    ui->setupUi(this);
}

AlertWindow::~AlertWindow()
{
    delete ui;
}

void AlertWindow::changeAlertMsg(QString msg)
{
    ui->MsgLabel->setText(msg);
}
