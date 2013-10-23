#include "database.h"

bool DatabaseManager::openDB()
    {
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

    #ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
     QString path(QDir::current().path());
    path.append(QDir::separator()).append("my.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    #else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName("my.db.sqlite");
    #endif

    // Open databasee
    return db.open();
    }
bool DatabaseManager::createTeble1()
{
    QSqlQuery query;
        QString   str  = "CREATE TABLE  IF NOT EXISTS  General ( "
                             "ID INTEGER PRIMARY KEY NOT NULL, "
                             "name   VARCHAR(15), "
                             "adress  VARCHAR(12),"
                                "time VARCHAR(12)"
                         ");";
        if (!query.exec(str)) {
            return false;

        }
        return true;
}
bool DatabaseManager::createTeble2()
{
    QSqlQuery query;
        QString   str  = "CREATE TABLE  IF NOT EXISTS Terminals ( "
                             "number INTEGER PRIMARY KEY NOT NULL, "
                             "tempreture  VARCHAR(15), "
                             "water_left  VARCHAR(12),"
                            "  volt5 VARCHAR(12),"
                                "volt12  VARCHAR(12),"
                            "money  VARCHAR(12),"
                            "power  VARCHAR(12),"
                                "carry_on VARCHAR(12),"
                                    "id VARCHAR(12),"
                                "timesale VARCHAR(12),"
                                "timewater VARCHAR(12)"
                         ");";
        if (!query.exec(str)) {
            return false;

        }
        return true;
}
bool DatabaseManager::insertinttable1(QString name, QString address,QString time)
{
    QSqlQuery query;
    QString strF =
              "INSERT INTO  General (name, adress,time) "
            "VALUES('%1', '%2','%3' );";

      QString  str = strF.arg(name)
                  .arg(address)
                  .arg(time);
        if (!query.exec(str)) {
            return false;
        }
        return true;
}
bool DatabaseManager::insertinttable2(QString temprete, QString water_left, QString volt5, QString volt12, QString money, QString power,
                                      QString carry_on, QString ID, QString timesale, QString timewater)
{
        QSqlQuery query;
    QString strF =
              "INSERT INTO  Terminals  (tempreture, water_left,volt5,volt12,money,power,carry_on,id,timesale,timewater) "
            "VALUES('%1', '%2','%3' ,'%4','%5','%6','%7','%8','%9','%10');";
    QString  str = strF.arg(temprete)
                .arg(water_left)
                .arg(volt5)
                .arg(volt12)
                .arg(money)
                .arg(power)
                .arg(carry_on)
                .arg(ID)
                .arg(timesale)
                .arg(timewater);
      if (!query.exec(str)) {
          return false;
            //qDebug()<< query.lastError();
      }
      return true;
}

QSqlError DatabaseManager::lastError()
    {
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
    }

bool DatabaseManager::deleteDB()
    {
    // Close database
    db.close();

    #ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("my.db.sqlite");
    path = QDir::toNativeSeparators(path);
    return QFile::remove(path);
    #else

    // Remove created database binary file
    return QFile::remove("my.db.sqlite");
    #endif
    }
