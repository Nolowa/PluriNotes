#ifndef IMAGE_H
#include <QFile>
#include <QImage>
#define IMAGE_H

#include "notextualnote.h"
#include "imageinterface.h"

class ImageInterface;

class Image: public NoTextualNote {
    QImage image;
    QString nameFile;
public:
    Image(QUuid identifier);
<<<<<<< HEAD:image.h
    void setImage(const QString& im);
    const QString& getnameFile() const;
    const QImage& getImage() const;
    ImageInterface* getInterface();

=======
    const QImage& getFile() const;
    Image(const Image& i):NoTextualNote(i),file(i.getFile()){}
    Note* save();
    void load(Note* n);
>>>>>>> 9cb9ff33adb691c711ec2803bd079498782ea2ac:notes/image.h
};

#endif // IMAGE_H
