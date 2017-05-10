#include "note.h"

//private:
void Note::setEdited(){
    edited=QDateTime::currentDateTime();
}


//pubic:
Note::Note(QUuid identifier) : identifier(identifier),created(QDateTime::currentDateTime()),edited(QDateTime::currentDateTime()){};

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

void Note::setTitle(const QString& t){
    title=t;
    setEdited();
}

/*
Note::~Note(){
    delete &identifier;
}
*/
