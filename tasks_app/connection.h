#ifndef CONNECTION_H
#define CONNECTION_H


#include<QtSql>
#include<iostream>


class Connection
{
private:
    QSqlDatabase tasks_database;
    int UserID;


public:
    Connection(){
        UserID = -1;
        tasks_database = QSqlDatabase::addDatabase("QSQLITE");
        tasks_database.setDatabaseName("C:/Users/Miko7/SQLite_databases/TasksApp.db");
        tasks_database.open();
    }


    QSqlDatabase getDatabase(){
        return tasks_database;
    }

    int getUserID(){
        return UserID;
    }

    bool LoginUser(QString login, QString password);

    bool RegisterUser(QString name, QString login, QString password);

    bool AddTask(QString title, QString description, QString date);


};
#endif // CONNECTION_H
