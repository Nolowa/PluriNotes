#include "image.h"

Image::Image(QUuid identifier): NoTextualNote(identifier){}
const QImage& Image::getFile() const {return file;}
