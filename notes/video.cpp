#include "video.h"
#include "interfaces/videointerface.h"

const QString Video::type = QString("Video");

Video::Video(QUuid identifier) : NoTextualNote(identifier),videoFile(new QMovie){}


Video::Video(QUuid identifier,const QString& filename):NoTextualNote(identifier),nameVideoFile(filename){
    videoFile = new QMovie;
}


Video::Video(QUuid identifier, QDateTime c,const QString& filename):NoTextualNote(identifier,c),nameVideoFile(filename){
    videoFile = new QMovie;
}

const QString& Video::getVideoFileName() const{
    return nameVideoFile;
}

NoteInterface* Video::getUI() const{
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
