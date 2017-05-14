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
    Sound(QUuid identifier,const QString& filename="");
    SoundInterface* getInterface();
    const QSound& getSound() const;
    const QString& getSoundFileName() const;
    void setSoundFile(const QString& name);

};

#endif // SOUND_H
