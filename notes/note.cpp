#include "note.h"

const QString Note::type = QString("Note");

Note::Note(QUuid identifier) : identifier(identifier),created(QDateTime::currentDateTime()),edited(QDateTime::currentDateTime()),state(active){}

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


State Note::getStates() const{
    return state;
}

/*
Note::Note(Note* n){
    identifier=n.getIdentifier();
    title=n.getTitle();
    created=n.getCreated();
    edited=n.getEdited();
    state=n.getStates();
}

*/

void Note::setCreated(QDateTime c){
    created=c;
}

void Note::setEdited(QDateTime e){
    edited=e;
}

const QString& Note::getType() const{
    return type;
}

/*QStandardItem *Note::clone() const
{
    return new Note(QUuid::createUuid());
}
*/

QString Note::getFilename() const {
    return filename;
}

void Note::setFilename(const QString& f) {
    filename=f;
}

Note::Note(QUuid identifier, QDateTime c):identifier(identifier),created(c),edited(QDateTime::currentDateTime()),state(active){}
