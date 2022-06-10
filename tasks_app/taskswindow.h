#ifndef TASKSWINDOW_H
#define TASKSWINDOW_H

#include "connection.h"
#include <QDialog>

namespace Ui {
class taskswindow;
}

class taskswindow : public QDialog
{
    Q_OBJECT

public:
    taskswindow(Connection con, QWidget *parent = nullptr);

    void setDb(Connection dbcon){
        this->databaseConnect = dbcon;
    }

    void setUserID(int newID){
        std::cout<<"inParameter"<<newID<<std::endl;
        this->UserID = QString::number(newID);
    }

    ~taskswindow();

    void downloadTasks();

private slots:
    void onAddButton(bool);


private:
    Ui::taskswindow *ui;
    Connection databaseConnect;
    QString UserID;

    void addTaskWidget(QString title, QString description, QString name);
};

#endif // TASKSWINDOW_H
