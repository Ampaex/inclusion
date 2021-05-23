#include "mainwindow.h"
#include "form.h"
#include "alertwindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Form login;
    AlertWindow login;
    login.move(QApplication::desktop()->screen()->rect().center() - login.rect().center());
    login.show();

    return a.exec();
}
