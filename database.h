#ifndef DATABASE_H
#define DATABASE_H
#include "notesmanager.h"
#include "notes/note.h"
#include <QtSql>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQuery>
#include <QObject>
#include <QComboBox>
#include <QStringList>

class Database : QObject
{
    NotesManager& notesManager;
    QStringList types;

    QString filename;
    QSqlDatabase db;
    bool open = false;
    bool ignoreManagerSignal = false;

    bool createTables();/**< créer les tables*/

    Q_OBJECT
public:
    Database(NotesManager& nm, const QString& filename);/**< fait appel à la fonction connectBd*/

    const Note& loadContent(int id, const QString&);
    void loadAll();
    ~Database();

public slots:
    void insertVersion(const NoteHolder& n);/**< insérer tous les infos d'une note dans BDD*/
    void updateStatus(const NoteHolder& n);
};

#endif // DATABASE_H
