#ifndef IMAGE_H
#include <QFile>
#include <QImage>
#define IMAGE_H

#include "note.h"


class Image: public Note {
    QString description;
    QImage file;
public:
    Image(QUuid identifier);
};

#endif // IMAGE_H
