#include "video.h"

Video::Video(QUuid identifier):NoTextualNote(identifier){}
const QVideoWidget& Video::getVideofile()const{return videofile;}
