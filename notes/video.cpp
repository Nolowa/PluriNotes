#include "video.h"

Video::Video(QUuid identifier,const QString& filename):NoTextualNote(identifier),nameVideoFile(filename){}

const QString& Video::getVideoFileName() const{
    return nameVideoFile;
}

VideoInterface* Video::getInterface(){
    return new VideoInterface(this);
}

const QMovie& Video::getVideo() const{
    return videoFile;
}

void Video::setVideoFile(const QString& name){
    nameVideoFile=name;
    videoFile.setFileName(name);
}

