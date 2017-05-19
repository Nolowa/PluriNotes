#ifndef VERSION_H
#define VERSION_H
#include "notesmanager.h"
#include <QtSql>
#include <iostream>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQuery>
#define q2c(string) string.toStdString()



class version
{
    static QSqlDatabase db;
    static int table_exist;
    static int open;
public:
    version();
    static bool connectBd(const QString& dbname);
    static void closeBd();
    static void createTables();
    static void insert(Note* n);
    static void parcourir(Note* n);
};




#endif // VERSION_H
