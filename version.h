#ifndef VERSION_H
#define VERSION_H
#include "notesmanager.h"
#include <QtSql>
#include <iostream>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQuery>
#include <QObject>
#include <QComboBox>
#include <QStringList>
#define q2c(string) string.toStdString()



class version
{
    static QSqlDatabase db;
    static int table_exist;
    static int open;
    NotesManager& nm;
public:
    version(NotesManager& n);
    static bool connectBd(const QString& dbname);
    static void closeBd();
    static void createTables();
    static void insert(const Note* n);
    static void parcourir(const Note* n);
    static void typeGenre(Note* n,int* num, QString& genre);
};



#endif // VERSION_H
