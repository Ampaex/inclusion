#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupLabel->setText("");

    connect(timer, SIGNAL(timeout()), this, SLOT(updateInterface()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QListWidget* MainWindow::getGroupList()
{
    return ui->listWidget_2;
}

QLabel* MainWindow::getLabelUsername()
{
    return ui->label_userName;
}

Ui::MainWindow* MainWindow::getUi()
{
    return ui;
}

void MainWindow::on_clearButton_clicked()
{
    ui->lineEdit->clear();
}

void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    stringstream datasrtm;
    Group requestedGroup = Group(item->text().toStdString());
    requestedGroup.addUser(client->user);
    datasrtm << requestedGroup; //Create a new group to send
    cout << "Requested group: " << datasrtm.str() <<endl;
    client->data = datasrtm.str();  //Send requested group

    //Wait for response from server
    while(!client->responseAvailable){};
    client->responseAvailable = false;

    updateUsers();

    //Change tab focus
    ui->tabWidget->setCurrentIndex(1);

    //Refresh time
    timer->start(1000);
}

void MainWindow::updateInterface()
{
    cout << "Updating with server" <<endl;
    stringstream datasrtm;
    Group requestedGroup = Group(client->group.getTitle());
    requestedGroup.addUser(client->user);
    datasrtm << requestedGroup;
    client->data = datasrtm.str();  //Send requested group

    //Wait for response from server
    while(!client->responseAvailable){};
    client->responseAvailable = false;

    updateUsers();

    updateChatBox();

    //Update label that indicates in which group is the user
    if(client->group.getTitle()!= "")
    {
        ui->groupLabel->setText(QString(client->group.getTitle().c_str()));
    }
    else
    {
        ui->groupLabel->setText("");
    }

}

void MainWindow::on_pushButton_clicked()
{
    sendToChatBox();
}

void MainWindow::on_lineEdit_returnPressed()
{
    sendToChatBox();
}

void MainWindow::sendToChatBox()
{
    QString inputText = ui->lineEdit->text(); //Get text from input box
    string inputText_s = inputText.toStdString();
    on_clearButton_clicked(); //Clear input box

    stringstream datasrtm;
    Message msg = Message(inputText_s,this->client->user.getLanguage(),this->client->user,false);


    datasrtm << "Group:" << client->group.getTitle() << "/" << msg; //Create a new group to send

    client->data = datasrtm.str();  //Send requested group
    //Wait for response from server
    while(!client->responseAvailable){};
    client->responseAvailable = false;

    updateChatBox();
}

void MainWindow::updateChatBox()
{
    //Update messages
    if(!client->group.getMessages().empty())
    {
        ui->listWidget->clear();
        for(Message mess: client->group.getMessages())
        {
            QListWidgetItem* line = new QListWidgetItem();
            if(mess.getUser().getName() == client->user.getName())
            {
                QString mess_qt = QString(mess.getUser().getName().c_str()) + QString(" >   ") ;
                mess_qt += QString(mess.getText(client->user.getLanguage()).c_str());
                line->setText(mess_qt);
                line->setTextAlignment(2);
            }
            else
            {
                QString mess_qt = QString(mess.getUser().getName().c_str()) + QString(" >   ") ;
                mess_qt += QString(mess.getText(client->user.getLanguage()).c_str());
                line->setText(mess_qt);
                line->setTextAlignment(0);
            }
            ui->listWidget->addItem(line);
        }
    }
    else
    {
        ui->listWidget->clear();
    }

    //If we are in a group then enable text input
    if(client->group.getTitle()!="")
    {
        ui->lineEdit->setReadOnly(false);
        ui->lineEdit->setPlaceholderText(QString(tr("Escribe aquí...")));
    }
}

void MainWindow::updateUsers()
{
    //Udate users
    if(!client->group.getUsers().empty())
    {
        ui->listWidget_1->clear();
        for(User us: client->group.getUsers())
        {
            QString us_qs = QString(us.getName().c_str());
            ui->listWidget_1->addItem(us_qs);
        }
    }
    else
    {
        ui->listWidget_1->clear();
    }
}
