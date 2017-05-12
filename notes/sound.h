#ifndef SOUND_H
#define SOUND_H

#include "notextualnote.h"
#include <QSound>


class Sound: public NoTextualNote{
    QSound soundfile;
public:
    Sound(QUuid identifier,const QString& filename);
    const QSound& getSoundfile()const;
    //Sound(const Sound& s):NoTextualNote(s),soundfile(s.getSoundfile()){}

};

#endif // SOUND_H
