#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_loginButton_clicked()
{
    username = ui->userName->text();
    if (!username.isEmpty())
    {
        this->hide();
        mainwindow.setUsername(username);
        mainwindow.show();
    }
}

void Form::on_comboBox_activated(const QString &arg1)
{

}
