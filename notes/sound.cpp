#include "sound.h"

Sound::Sound(QUuid identifier, const QString& filename):NoTextualNote(identifier),soundFile(new QSound(filename)),soundFileName(filename){}

SoundInterface* Sound::getInterface(){
    return new SoundInterface(this);
}

const QSound& Sound::getSound() const{
    return *soundFile;
}

const QString& Sound::getSoundFileName() const{
    return soundFileName;
}

void Sound::setSoundFile(const QString& name){
    soundFileName=name;
    delete soundFile;
    soundFile= new QSound (name);
}
