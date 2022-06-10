#include "taskswindow.h"
#include "connection.h"
#include "./ui_taskswindow.h"

taskswindow::taskswindow(Connection con, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskswindow)
{
    databaseConnect = con;
    UserID = QString::number(con.getUserID());
    ui->setupUi(this);
    ui->taskBox->hide();
    ui->addDate->setDateTime(QDateTime::currentDateTime());
    std::cout<<UserID.toStdString()<<std::endl;
    downloadTasks();
}

taskswindow::~taskswindow()
{
    delete ui;
}

void taskswindow::onAddButton(bool)
{
    QString title, desc, date;
    title = ui->addTitle->text();
    desc = ui->addDescription->document()->toPlainText();
    if(ui->addDate->dateTime() < QDateTime::currentDateTime()){
        ui->addDate->setDateTime(QDateTime::currentDateTime());
        ui->communicatLabel->setText("Niepoprawna data");
        return;
    }

    if(title.length() < 3){
        ui->communicatLabel->setText("Niepoprawna nazwa");
        return;
    }

    date = ui->addDate->dateTime().toString("yyyy-MM-dd hh:mm");
    std::cout<< title.toStdString() << " : "<< desc.toStdString() <<  " : "<< date.toStdString() << std::endl;
    databaseConnect.AddTask(title, desc, date);
    ui->addTitle->clear();
    ui->addDescription->clear();
    ui->addDate->setDateTime(QDateTime::currentDateTime());
    ui->communicatLabel->setText("Dodano zadanie : " + title);

    addTaskWidget(title, desc, date);
    return;
}


void taskswindow::downloadTasks(){
    std::cout<< UserID.toStdString() << std::endl;
    QSqlDatabase tasks_database = databaseConnect.getDatabase();
    QSqlQuery *loginQuery = new QSqlQuery(tasks_database);
    if(loginQuery->exec("select EventName, Description, Date from Events where UserID = '" + UserID + "'")){
        while(loginQuery->next()){
            std::cout << loginQuery->value(0).toString().toStdString() <<": "<< loginQuery->value(1).toString().toStdString() <<": "<<loginQuery->value(2).toString().toStdString() <<": "<< std :: endl;

            QString title, desc, date;
            title = loginQuery->value(0).toString();
            desc = loginQuery->value(1).toString();
            date = loginQuery->value(2).toString();

            QDateTime curr_task_time = QDateTime::fromString(date, "yyyy-MM-dd hh:mm");
            if(curr_task_time > QDateTime::currentDateTime()){
                addTaskWidget(title, desc, date);
            }
        }
    }

}


void taskswindow::addTaskWidget(QString title, QString description, QString date){
    auto* taskBox = new QGroupBox(ui->taskAreaWidgets);
    taskBox->setObjectName(QString::fromUtf8("taskBox"));
    taskBox->setMinimumSize(QSize(597, 180));
    taskBox->setCheckable(false);
    taskBox->setChecked(false);
    auto* taskTitle = new QLabel(taskBox);
    taskTitle->setObjectName(QString::fromUtf8("taskTitle"));
    taskTitle->setGeometry(QRect(30, 20, 431, 31));
    QFont font1;
    font1.setFamilies({QString::fromUtf8("Lato")});
    font1.setPointSize(15);
    font1.setBold(true);
    taskTitle->setFont(font1);
    auto* taskDesc = new QLabel(taskBox);
    taskDesc->setObjectName(QString::fromUtf8("taskDesc"));
    taskDesc->setGeometry(QRect(30, 60, 521, 51));
    QFont font2;
    font2.setFamilies({QString::fromUtf8("Lato")});
    font2.setPointSize(12);
    taskDesc->setFont(font2);
    auto* taskDate = new QLabel(taskBox);
    taskDate->setObjectName(QString::fromUtf8("taskDate"));
    taskDate->setGeometry(QRect(110, 120, 391, 31));
    QFont font3;
    font3.setFamilies({QString::fromUtf8("Lato")});
    font3.setPointSize(14);
    taskDate->setFont(font3);

    taskBox->setTitle(QString());
    taskTitle->setText(QCoreApplication::translate("taskswindow", title.toLocal8Bit().data() , nullptr));
    taskDesc->setText(QCoreApplication::translate("taskswindow", description.toLocal8Bit().data(), nullptr));
    taskDate->setText(QCoreApplication::translate("taskswindow", date.toLocal8Bit().data(), nullptr));
    ui->verticalLayout_3->addWidget(taskBox);

}
