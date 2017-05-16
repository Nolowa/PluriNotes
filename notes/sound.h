#ifndef SOUND_H
#define SOUND_H

#include "notes/notextualnote.h"
#include <QSound>

#include "interfaces/soundinterface.h"
class SoundInterface;

class Sound: public NoTextualNote{
    QSound* soundFile;
    QString soundFileName;
    static const QString type;
public:
    Sound(QUuid identifier,const QString& filename="");

    SoundInterface* getInterface();

    const QSound& getSound() const;
    const QString& getSoundFileName() const;
    void setSoundFile(const QString& name);

    const QString& getType() const;

};

#endif // SOUND_H
