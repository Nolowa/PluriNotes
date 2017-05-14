#ifndef IMAGE_H
#define IMAGE_H

#include <QFile>
#include <QImage>
#include "notextualnote.h"
#include "imageinterface.h"

class ImageInterface;

class Image: public NoTextualNote {
    QImage image;
    QString nameFile;
public:
    Image(QUuid identifier);
    void setImage(const QString& im);
    const QString& getnameFile() const;
    const QImage& getImage() const;
    ImageInterface* getInterface();

    const QImage& getFile() const;
    Note* save();
    void load(Note* n);
};

#endif // IMAGE_H
