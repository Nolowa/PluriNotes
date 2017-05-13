#include "sound.h"

Sound::Sound(QUuid identifier, const QString& filename):NoTextualNote(identifier),soundfile(filename){}
const QSound& Sound::getSoundfile()const{return soundfile;}

