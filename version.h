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

    static int open;
    NotesManager& nm;
public:
    version(NotesManager& n);/**< fait appel à la fonction connectBd*/
    static bool connectBd(const QString& dbname);/**< connecter à la base de donnée */
    static void closeBd();/**< déconnecter*/
    static void createTables();/**< créer les tables*/
    static void insert(const Note* n);/**< insérer tous les infos d'une note dans BDD*/
    static void typeGenre(Note* n,int* num, QString& genre);/**< vérifier le type de n*/
};




#endif // VERSION_H
