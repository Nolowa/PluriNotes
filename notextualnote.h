#ifndef NOTEXTUALNOTE_H
#define NOTEXTUALNOTE_H

#include "note.h"

class NoTextualNote: public Note{
    QString description;

public:
    NoTextualNote(QUuid identifier);
    const QString& getDescription() const;
    void setDescription(const QString& d);
};

#endif // NOTEXTUALNOTE_H
