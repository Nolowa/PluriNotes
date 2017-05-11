#ifndef PLURINOTES_H
#define PLURINOTES_H

#include <QMainWindow>
#include <QtWidgets>
#include "notesmanager.h"

class PluriNotes: public QMainWindow {
    //Q_OBJECT

    NotesManager* notesManager;

public:
    PluriNotes(NotesManager& n);

signals:

public slots:
    //void saveNote();

};

#endif // PLURINOTES_H
