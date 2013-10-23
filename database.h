#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QSqlQuery>
class DatabaseManager : public QObject
    {
    public:
       // DatabaseManager(QObject *parent = 0);
        //~DatabaseManager();

    public:
         bool createTeble1();
         bool createTeble2();
        bool openDB();
        bool deleteDB();
        bool insertinttable1(QString name, QString address,QString time);
        bool insertinttable2(QString temprete,QString water_left,QString volt5,QString volt12,QString money,QString power,
                             QString carry_on, QString ID, QString timesale, QString timewater);
        QSqlError lastError();

    private:
        QSqlDatabase db;
    };

#endif // DATABASE_H
