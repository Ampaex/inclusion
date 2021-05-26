#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <client.h>
#include <QTimer>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Client* client;
    QListWidget* getGroupList();
    QLabel* getLabelUsername();
    void updateChatBox();
    void updateUsers();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clearButton_clicked();
    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);
    void updateInterface();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer = new QTimer(this);
};
#endif // MAINWINDOW_H
