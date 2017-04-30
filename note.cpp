#include "note.h"
#include <QString>

Note::Note()
{


}

const QUuid Note::getIdentifier() const{
    return identifier;
}

const QString Note::getTitle() const{
    return title;
}

const QDateTime Note::getCreated() const{
    return created;
}

const QDateTime Note::getEdited() const{
    return edited;
}

/*
Note::~Note(){
    delete &identifier;
}
*/
