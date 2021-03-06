#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <connection.h>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void onLoginButtonPressed(bool);
    void onRegisterButtonPressed(bool);

private:
    Ui::MainWindow *ui;
    Connection databaseConnect;
    int UserID;

    void AfterLogin(int);

};
#endif // MAINWINDOW_H
