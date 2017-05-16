#ifndef VIDEO_H
#define VIDEO_H

#include "notes/notextualnote.h"
#include <QVideoWidget>
#include <QMovie>

#include "interfaces/videointerface.h"

class VideoInterface;

class Video: public NoTextualNote{
    QMovie videoFile;
    QString nameVideoFile;
    static const QString type;

public:
    Video(QUuid identifier,const QString& filename="");

    VideoInterface* getInterface();

    const QString& getVideoFileName() const;
    const QMovie& getVideo() const;
    void setVideoFile(const QString& name); // change nameVideoFile et videoFile

    const QString& getType() const;
};

#endif // VIDEO_H
