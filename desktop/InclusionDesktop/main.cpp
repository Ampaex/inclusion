#include "mainwindow.h"
#include "form.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form login;
    login.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
