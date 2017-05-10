#ifndef VIDEO_H
#define VIDEO_H

#include "note.h"
#include <QVideoWidget>

class Video: public Note{
    QString description;
    QVideoWidget videofile;

public:
    Video(QUuid identifier);
};

#endif // VIDEO_H
