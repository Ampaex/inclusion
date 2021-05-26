#include "mainwindow.h"
#include "form.h"
#include "alertwindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    Form login;
    login.trans = &translator;
    login.app = &a;
    login.move(QApplication::desktop()->screen()->rect().center() - login.rect().center());
    login.show();

    return a.exec();
}
