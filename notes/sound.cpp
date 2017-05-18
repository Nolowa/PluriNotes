#include "sound.h"

const QString Sound::type = QString("Son");

Sound::Sound(QUuid identifier, const QString& filename):NoTextualNote(identifier),soundFile(new QSound(filename)),soundFileName(filename){}

QWidget* Sound::getUI() const{
    return new SoundInterface(*this);
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

const QString& Sound::getType() const{
    return type;
}
