#include "image.h"

Image::Image(QUuid identifier): NoTextualNote(identifier){}
const QImage& Image::getFile() const {return file;}
Note* Image::save(){
    Note* n=new Image(*this);
    return n;
}

void Image::restore(Note* n){
    Image* nouveau;
    nouveau=static_cast<Image*>(n);
    this->setIdentifier(nouveau->getIdentifier());
    this->setTitle(nouveau->getTitle());
    this->setCreated(nouveau->getCreated());
    this->setEdited(nouveau->getEdited());
    this->setState(nouveau->getStates());
    this->setDescription(nouveau->getDescription());
    file=nouveau->getFile();
}
