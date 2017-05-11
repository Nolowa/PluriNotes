#ifndef SOUND_H
#define SOUND_H

#include "notextualnote.h"
#include <QSound>


class Sound: public NoTextualNote{
    QSound soundfile;
public:
    Sound(QUuid identifier,const QString& filename);

};

#endif // SOUND_H
