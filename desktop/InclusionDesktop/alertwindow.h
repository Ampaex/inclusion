#ifndef ALERTWINDOW_H
#define ALERTWINDOW_H

#include <QDialog>

namespace Ui {
class AlertWindow;
}

class AlertWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AlertWindow(QWidget *parent = nullptr);
    ~AlertWindow();

    void changeAlertMsg(QString msg);

private:
    Ui::AlertWindow *ui;
};

#endif // ALERTWINDOW_H
