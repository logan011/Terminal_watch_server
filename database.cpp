#include "database.h"

database::database()
{

}
database::database(const char *str)
{
    base = QSqlDatabase::addDatabase("SQLLITE");
    base.setDatabaseName(str);
    if(!base.open())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Cannot conect to DataBase!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}
void database::createDB()
{
    base = QSqlDatabase::addDatabase("SQLLITE");
    base.setDatabaseName("Water_Terminal");
    if(!base.open())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Cannot conect to DataBase!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}
