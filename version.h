#ifndef VERSION_H
#define VERSION_H
#include "notesmanager.h"
#include <QtSql>
#include <iostream>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQuery>
#include <QObject>
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
};

class bbd : public QObject
{
    NotesManager& nm;
    Q_OBJECT
public:
    bbd(NotesManager& n);
public slots:
    void insert(const Note& n);
};


#endif // VERSION_H
