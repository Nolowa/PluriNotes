#ifndef SOUND_H
#define SOUND_H

#include "note.h"
#include <QSound>


class Sound: public Note{
    QString description;
    QSound soundfile;
public:
    Sound(QUuid identifier,const QString& filename);
};

#endif // SOUND_H
