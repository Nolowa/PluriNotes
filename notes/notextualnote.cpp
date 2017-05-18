#include "notextualnote.h"

NoTextualNote::NoTextualNote(QUuid identifier):Note(identifier){}

NoTextualNote::NoTextualNote(QUuid identifier, QDateTime c):Note(identifier,c){}
const QString& NoTextualNote::getDescription() const{
    return description;
}

void NoTextualNote::setDescription(const QString& d){
    description=d;
    setEdited();
}

NoTextualNote::~NoTextualNote(){}
