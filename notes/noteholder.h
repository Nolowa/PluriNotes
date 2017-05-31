#ifndef NOTEIDENTIFIER_H
#define NOTEIDENTIFIER_H

#include <QUuid>
#include <QDateTime>

#include "notes/note.h"
#include "utils.h"

typedef enum {ACTIVE, ARCHIVED, DELETED} NoteState;// active=0, non_editable=1, sursis=2

class NoteHolder
{
    const QUuid identifier;
    const QDateTime created;
    const Note * lastVersion = nullptr;
    int status = 0;


public:
    NoteHolder() : identifier(QUuid::createUuid()){}
    NoteHolder(QString uuid, QDateTime created, int status) : identifier(QUuid(uuid)), created(created), status(static_cast<NoteState>(status)){}

    const QUuid getId() const{ return identifier; }
    const QDateTime getCreated() const { return created; }
    const Note& getLastVersion() const{ return *lastVersion; }
    int getState() const { return status; }
    bool isActive() const { return status == NoteState::ACTIVE; }
    bool isDeleted() const { return status == NoteState::DELETED; }

    void update(const Note& newVersion);

    bool operator==(const NoteHolder& id2) const { return identifier == id2.identifier; }
    bool operator<(const NoteHolder& id2) const { return identifier < id2.identifier; }
    operator QString() const {

        return lastVersion ? lastVersion->getTitle() : "";
    }

};

#endif // NOTEIDENTIFIER_H
