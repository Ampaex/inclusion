#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateInterface()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QListWidget* MainWindow::getGroupList(){return ui->listWidget_2;};
QLabel* MainWindow::getLabelUsername(){return ui->label_userName;};

void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
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
    if(!client->group.getUsers().empty())
    {
        for(User us: client->group.getUsers())
        {
            QString us_qs = QString(us.getName().c_str());
            ui->listWidget_1->addItem(us_qs);
        }
        ui->tabWidget->setCurrentIndex(0);
    }
    timer->start(2000);
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

    //Update messages
    if(!client->group.getMessages().empty())
    {
        ui->listWidget->clear();
        for(Message mess: client->group.getMessages())
        {
            QString mess_qt = QString(mess.getText(client->user.getLanguage()).c_str());
            ui->listWidget->addItem(mess_qt);
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    QString inputText = ui->textEdit->toPlainText(); //Get text from input box
    string inputText_s = inputText.toStdString();
    on_clearButton_clicked(); //Clear input box

    stringstream datasrtm;
    Message msg = Message(inputText_s,this->client->user.getLanguage(),this->client->user,false);


    datasrtm << "Group:" << client->group.getTitle() << "/" << msg; //Create a new group to send

    client->data = datasrtm.str();  //Send requested group
    //Wait for response from server
    while(!client->responseAvailable){};
    client->responseAvailable = false;


    cout <<endl<< "------Grupo: " << client->group <<endl;
    //Update messages
    if(!client->group.getMessages().empty())
    {
        ui->listWidget->clear();
        cout << "ENTROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"<<endl;
        for(Message mess: client->group.getMessages())
        {
            cout << "message" << mess.getText("es") << endl;
            QString mess_qt = QString(mess.getText(client->user.getLanguage()).c_str());
            ui->listWidget->addItem(mess_qt);
        }
    }

}
