#include "sound.h"

<<<<<<< HEAD:sound.cpp
Sound::Sound(QUuid identifier, const QString& filename):NoTextualNote(identifier),soundFile(new QSound(filename)),soundFileName(filename){}
=======
Sound::Sound(QUuid identifier, const QString& filename):NoTextualNote(identifier),soundfile(filename){}
const QSound& Sound::getSoundfile()const{return soundfile;}
>>>>>>> 9cb9ff33adb691c711ec2803bd079498782ea2ac:notes/sound.cpp

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
