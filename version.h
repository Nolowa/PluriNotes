#ifndef VERSION_H
#define VERSION_H
#include "notesmanager.h"
#include <QtSql>
#include <iostream>
#define q2c(string) string.toStdString()



class version
{
    static QSqlDatabase db;
    static int table_exist;
    static int open;
public:
    version();
    static bool connectBd();
    static void closeBd();
    static void createTables();
};




#endif // VERSION_H
