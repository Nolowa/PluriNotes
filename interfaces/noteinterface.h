#ifndef GENERALINTERFACE_H
#define GENERALINTERFACE_H

#include <QWidget>
#include "notes/note.h"

class NoteManager;
class Note;

class NoteInterface : public QWidget{
    Q_OBJECT

    //virtual const Note * save() = 0;
public:
    explicit NoteInterface(QWidget *parent = 0);

signals:
    void newVersion(const Note*);
};

#endif // GENERALINTERFACE_H
