#include "mainwindow.h"
#include "connection.h"
#include "taskswindow.h"
#include "./ui_mainwindow.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    databaseConnect = Connection();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onLoginButtonPressed(bool)
{
    QString login, password;
    login = ui->loginLogin->text();
    password = ui->loginPassword->text();
    ui->loginPassword->clear();
    ui->loginLogin->clear();
    //std::cout << login.toStdString() <<": "<< password.toStdString() << std :: endl;
    if(databaseConnect.LoginUser(login, password)){
        ui->communicatLabel->setText("Logowanie OK");
        std::cout << databaseConnect.getUserID() << std::endl;
        UserID = databaseConnect.getUserID();
        AfterLogin(UserID);
    } else{
        ui->communicatLabel->setText("Podano niepoprawne dane");
    }
    return;
}


void MainWindow::onRegisterButtonPressed(bool)
{
    QString login, password, password2, name;
    login = ui->registerLogin->text();
    password = ui->registerPassword->text();
    password2 = ui->registerPassword_2->text();
    name = ui->registerName->text();
    int x = QString::compare(password, password2, Qt::CaseInsensitive);
    if(x != 0){
        ui->communicatLabel->setText("Podane hasła muszą być takie same");
        ui->registerPassword->clear();
        ui->registerPassword_2->clear();
        return;

    }
    if(password.length() < 6){
        ui->communicatLabel->setText("Hasło musi składać się z przynajmniej 6 znaków");
        ui->registerPassword->clear();
        ui->registerPassword_2->clear();
        return;
    }
    if(login.length() > 1 && name.length() > 1){
        if(databaseConnect.RegisterUser(name, login, password)){
            ui->communicatLabel->setText("Pomyślnie utworzono");
            UserID = databaseConnect.getUserID();
            AfterLogin(UserID);
        }else{
            ui->communicatLabel->setText("Taki użytkownik już istnieje");
        }
    }
    ui->registerLogin->clear();
    ui->registerName->clear();
    ui->registerPassword->clear();
    ui->registerPassword_2->clear();
    return;
}


void MainWindow::AfterLogin(int usrID){
    this->hide();
    taskswindow* tasksW = new taskswindow(databaseConnect);
    tasksW->exec();
}
