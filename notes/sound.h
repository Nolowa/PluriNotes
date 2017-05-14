#ifndef SOUND_H
#define SOUND_H

#include "notextualnote.h"
#include <QSound>

#include "soundinterface.h"
class SoundInterface;

class Sound: public NoTextualNote{
    QSound* soundFile;
    QString soundFileName;
public:
<<<<<<< HEAD:sound.h
    Sound(QUuid identifier,const QString& filename="");
    SoundInterface* getInterface();
    const QSound& getSound() const;
    const QString& getSoundFileName() const;
    void setSoundFile(const QString& name);
=======
    Sound(QUuid identifier,const QString& filename);
    const QSound& getSoundfile()const;
    //Sound(const Sound& s):NoTextualNote(s),soundfile(s.getSoundfile()){}
>>>>>>> 9cb9ff33adb691c711ec2803bd079498782ea2ac:notes/sound.h

};

#endif // SOUND_H
