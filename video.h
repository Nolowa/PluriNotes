#ifndef VIDEO_H
#define VIDEO_H

#include "notextualnote.h"
#include <QVideoWidget>

class Video: public NoTextualNote{
    QVideoWidget videofile;

public:
    Video(QUuid identifier);
    const QVideoWidget& getVideofile()const;
    //Video(const Video& v):NoTextualNote(v),videofile(v.getVideofile()){}  erreur

};

#endif // VIDEO_H
