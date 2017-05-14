#include "notes/image.h"

Image::Image(QUuid identifier): NoTextualNote(identifier){}


Note* Image::save(){
    Note* n=new Image(*this);
    return n;
}


/*
void Image::load(Note* n){
    Image* nouveau;
    nouveau=static_cast<Image*>(n);
    this->setTitle(nouveau->getTitle());
    this->setCreated(nouveau->getCreated());
    this->setEdited(QDateTime::currentDateTime());
    this->setState(nouveau->getStates());
    this->setDescription(nouveau->getDescription());
    //a rajouter, il me semble
    //image=nouveau->getFile();
    //nameFile=nouveau->getnameFile();
}
*/
