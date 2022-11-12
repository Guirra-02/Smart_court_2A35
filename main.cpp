#include "mainwindow.h"

#include <QApplication>
#include <QString>
#include <QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSqlDatabase db= QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Qtproject");
db.setUserName("melek");
db.setPassword("Gui02");
    if(db.open())
    {w.show();
            /*QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);*/

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    w.show();
    return a.exec();
}