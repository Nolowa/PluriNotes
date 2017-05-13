#ifndef IMAGE_H
#include <QFile>
#include <QImage>
#define IMAGE_H

#include "notextualnote.h"


class Image: public NoTextualNote {
    QImage file;
public:
    Image(QUuid identifier);
    const QImage& getFile() const;
    Image(const Image& i):NoTextualNote(i),file(i.getFile()){}
    Note* save();
    void load(Note* n);
};

#endif // IMAGE_H
