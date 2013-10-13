#ifndef DATABASE_H
#define DATABASE_H

class database
{
public:
    database();
    database(const char *);
    static void createDB();
private:
    QSqlDatabase base;

};

#endif // DATABASE_H
