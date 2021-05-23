#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->client = Client();
    this->client.startConnection((char*)"127.0.0.1",12345);
}

Form::~Form()
{
    delete ui;
}

void Form::on_loginButton_clicked()
{
    username = ui->userName->text();
    switch(ui->comboBox->currentIndex())
    {
        case 0:
            language = QString("es");
        break;

        case 1:
            language = QString("en");
        break;

        case 3:
            language = QString("zh");
        break;
    }
    string username_s = username.toStdString();
    string language_s = language.toStdString();
    if(!username.isEmpty())
    {
        stringstream dataStream;
        dataStream << User(username.toStdString(), language.toStdString());
        client.data = dataStream.str();

        //Wait for response from server
        while(!client.responseAvailable);
        client.responseAvailable = false;

        if (!client.groups.empty())
        {
            this->hide();
            mainwindow.client = &(this->client);

            //Sets client username and language
            client.setUser(User(username_s,language_s));

            //Fill groups box
            for(string elem:client.groups)
            {
                QString elem_qs = QString(elem.c_str());
                mainwindow.getGroupList()->addItem(elem_qs);
            }

            mainwindow.getLabelUsername()->setText(username);
            mainwindow.move(QApplication::desktop()->screen()->rect().center() - mainwindow.rect().center());
            mainwindow.show();

        }
    }
}

void Form::on_comboBox_activated(const QString &arg1)
{

}
