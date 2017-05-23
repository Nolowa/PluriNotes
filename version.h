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
};

/*
class bbd : public QObject
{
    Q_OBJECT
private:
    NotesManager& nm;
    const Note* no;

public:
    bbd(NotesManager& n,const Note* notes);

public slots:
    void insert();
};*/


#endif // VERSION_H
