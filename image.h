#ifndef IMAGE_H
#include <QFile>
#include <QImage>
#define IMAGE_H

#include "notextualnote.h"


class Image: public NoTextualNote {
    QImage file;
public:
    Image(QUuid identifier);

};

#endif // IMAGE_H
