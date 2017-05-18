#include "video.h"

const QString Video::type = QString("Vidéo");

Video::Video(QUuid identifier,const QString& filename):NoTextualNote(identifier),nameVideoFile(filename){
    videoFile = new QMovie;
}

const QString& Video::getVideoFileName() const{
    return nameVideoFile;
}

QWidget* Video::getUI() const{
    return new VideoInterface(*this);
}

const QMovie& Video::getVideo() const{
    return *videoFile;
}

void Video::setVideoFile(const QString& name){
    nameVideoFile=name;
    videoFile->setFileName(name);
}

const QString& Video::getType() const{
    return type;
}
