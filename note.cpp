#include "note.h"


Note::Note(QUuid identifier) : identifier(identifier),created(QDateTime::currentDateTime()),edited(QDateTime::currentDateTime()),
state(active){};

Note::~Note(){}

const QUuid Note::getIdentifier() const{
    return identifier;
}

const QString& Note::getTitle() const{
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

void Note::setState(State s){
    state=s;
}

const QString Note::getState() const{ //{active, non_editable,sursis}
    if(state==0)
        return QString("active");
    else if(state==1)
        return QString("non_editable");
        else
        return QString("sursis");
}

void Note::setEdited(){
    edited=QDateTime::currentDateTime();
}

