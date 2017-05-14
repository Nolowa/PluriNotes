#include "image.h"

Image::Image(QUuid identifier): NoTextualNote(identifier){}

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
