#ifndef VIDEO_H
#define VIDEO_H

#include "notextualnote.h"
#include <QVideoWidget>
#include <QMovie>

#include "videointerface.h"

class VideoInterface;

class Video: public NoTextualNote{
    QMovie videoFile;
    QString nameVideoFile;

public:
<<<<<<< HEAD:video.h
    Video(QUuid identifier,const QString& filename="");
    VideoInterface* getInterface();
    const QString& getVideoFileName() const;
    const QMovie& getVideo() const;
    void setVideoFile(const QString& name); // change nameVideoFile et videoFile
=======
    Video(QUuid identifier);
    const QVideoWidget& getVideofile()const;
    //Video(const Video& v):NoTextualNote(v),videofile(v.getVideofile()){}  erreur
>>>>>>> 9cb9ff33adb691c711ec2803bd079498782ea2ac:notes/video.h

};

#endif // VIDEO_H
