#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    void onClick();
    ~Form();

private slots:
    void on_loginButton_clicked();

private:
    Ui::Form *ui;
    QString username;
    MainWindow mainwindow;
};

#endif // FORM_H
