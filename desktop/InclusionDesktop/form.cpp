#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "alertwindow.h"
#include <QMessageBox>

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

        case 2:
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

        //Wait because in release version does not give enough time to fill group data
        this->thread()->msleep(50);

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

            loadTranslation(language);
            mainwindow.getUi()->retranslateUi(&mainwindow);
            mainwindow.getLabelUsername()->setText(username);
            mainwindow.move(QApplication::desktop()->screen()->rect().center() - mainwindow.rect().center());
            mainwindow.show();

        }
        else
        {
            QMessageBox alert;
            QPixmap icon(app->applicationDirPath()+"/../../media/images/Alert.png");
            alert.setIconPixmap(icon);
            alert.setText(tr("El usuario ya existe, escoja otro"));
            alert.exec();
        }
    }
}

void Form::loadTranslation(QString lang)
{

    QString path = this->app->applicationDirPath() + "/InclusionDesktop_" + lang;

    if(!this->trans->load(path))
    {
        QMessageBox alert;
        QPixmap icon(app->applicationDirPath()+"/../../media/images/Alert.png");
        alert.setIconPixmap(icon);
        alert.setText(tr("No ha sido posible cargar el idioma"));
        alert.exec();
    }
    else
    {
        this->app->installTranslator(this->trans);
    }

}

void Form::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            loadTranslation(QString("es"));
        break;

        case 1:
            loadTranslation(QString("en"));
        break;

        case 2:
            loadTranslation(QString("zh"));
        break;
    }
    ui->retranslateUi(this);
}
