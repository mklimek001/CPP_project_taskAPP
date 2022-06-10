#include <connection.h>


bool Connection::LoginUser(QString login, QString password){
    int currID;
    QSqlQuery *loginQuery = new QSqlQuery(tasks_database);
    if(loginQuery->exec("select ID from Users where Login = '" + login + "' and Password = '" + password + "'")){
        int counter = 0;
        while(loginQuery->next()){
            currID = loginQuery->value(0).toInt();
            counter++;
        }
        if(counter == 1){
            UserID = currID;
            std::cout << QString::number(UserID).toStdString() << std::endl;
            return true;
        }

    }
    return false;
}


bool Connection::RegisterUser(QString name, QString login, QString password)
{
    QSqlQuery *checkQuery = new QSqlQuery(tasks_database);
    if(checkQuery->exec("select ID from Users where Login = '" + login + "' and Password = '" + password + "'")){
        int counter = 0;
        while(checkQuery->next()){
            counter++;
        }
        if(counter > 0){
            return false;
        }
    }

    int max_index = 0;
    int curr_index;
    QSqlQuery *registerQuery = new QSqlQuery(tasks_database);
    if(registerQuery->exec("select ID from Users")){
        while(registerQuery->next()){
            curr_index = registerQuery->value(0).toInt();
            if(curr_index > max_index){
                max_index = curr_index;
            }
        }
    }
    UserID = max_index;
    registerQuery->exec("INSERT INTO Users (ID, Login, Password, Name) VALUES ("+ QString::number(max_index+1) +", '"+ login +"','"+ password +"','"+ name +"');");
    return true;
}


bool Connection::AddTask(QString title, QString description, QString date)
{
    int max_index = 0;
    int curr_index;
    QSqlQuery *registerQuery = new QSqlQuery(tasks_database);
    if(registerQuery->exec("select ID from Events")){
        while(registerQuery->next()){
            curr_index = registerQuery->value(0).toInt();
            if(curr_index > max_index){
                max_index = curr_index;
            }
        }
    }

    registerQuery->exec("insert into Events (ID, UserID, EventName, Description, Date) values('"+ QString::number(max_index+1) +"','"+ QString::number(UserID) +"', '"+ title +"', '"+ description +"','"+ date +"');");

    return true;
}








