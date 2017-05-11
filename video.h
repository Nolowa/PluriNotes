#ifndef VIDEO_H
#define VIDEO_H

#include "notextualnote.h"
#include <QVideoWidget>

class Video: public NoTextualNote{
    QVideoWidget videofile;

public:
    Video(QUuid identifier);

};

#endif // VIDEO_H
