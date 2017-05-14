#include "video.h"

<<<<<<< HEAD:video.cpp
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
=======
Video::Video(QUuid identifier):NoTextualNote(identifier){}
const QVideoWidget& Video::getVideofile()const{return videofile;}
>>>>>>> 9cb9ff33adb691c711ec2803bd079498782ea2ac:notes/video.cpp
