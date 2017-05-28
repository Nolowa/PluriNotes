#ifndef GENERALINTERFACE_H
#define GENERALINTERFACE_H

#include <QWidget>
#include "notes/note.h"
#include <iostream>
#include <QDateTime>
#include <QDebug>
#include <QSqlQuery>
#include <QStringList>


class NoteManager;
class Note;

class NoteInterface : public QWidget{
    Q_OBJECT

    //virtual const Note * save() = 0;
public:
    explicit NoteInterface(QWidget *parent = 0);

signals:
    void newVersion(const Note*);
    void loadVersion(const Note*);// signal pour mettre à jour NoteListView arpès chargement d'une ancienne version
};

#endif // GENERALINTERFACE_H
