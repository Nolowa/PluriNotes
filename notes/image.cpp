#include "image.h"

const QString Image::type = QString("Image");

Image::Image(QUuid identifier): NoTextualNote(identifier){}
Image::Image(QUuid identifier, QDateTime c):NoTextualNote(identifier,c){}
const QImage& Image::getImage() const{
    return image;
}

ImageInterface* Image::getInterface(){
    return new ImageInterface(this);
}

void Image::setImage(const QString &im){
    nameFile=im;
    image=QImage(im);
}

const QString& Image::getnameFile() const{
    return nameFile;
}


Note* Image::save(){
    Note* n=new Image(*this);
    return n;
}

void Image::load(Note* n){
    Image* nouveau;
    nouveau=static_cast<Image*>(n);
    this->setTitle(nouveau->getTitle());
    this->setCreated(nouveau->getCreated());
    this->setEdited(QDateTime::currentDateTime());
    this->setState(nouveau->getStates());
    this->setDescription(nouveau->getDescription());
    this->setImage(nouveau->getnameFile());
}

const QString& Image::getType() const{
    return type;
}


