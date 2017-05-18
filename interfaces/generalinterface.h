#ifndef GENERALINTERFACE_H
#define GENERALINTERFACE_H

#include <QWidget>
#include "notes/note.h"

class NoteManager;

class GeneralInterface : public QWidget{
    Q_OBJECT
public:
    explicit GeneralInterface(QWidget *parent = 0);

signals:
    void newVersion(const Note*);
};

#endif // GENERALINTERFACE_H
