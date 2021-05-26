#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QDesktopWidget>
#include "mainwindow.h"
#include <client.h>
#include <thread>
#include <QTranslator>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    void onClick();
    QTranslator* trans;
    QApplication* app;
    void loadTranslation(QString lang);
    ~Form();

private slots:
    void on_loginButton_clicked();

private:
    Ui::Form *ui;
    QString username;
    QString language;
    MainWindow mainwindow;
    Client client;
};

#endif // FORM_H
