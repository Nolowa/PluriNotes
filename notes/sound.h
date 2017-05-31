#ifndef SOUND_H
#define SOUND_H

#include "notes/notextualnote.h"
#include <QSound>
#include "interfaces/content-editor/soundinterface.h"
class SoundInterface;

/*! Classe Sound, classe fille de NoTextualNote*/
class Sound: public NoTextualNote{
    QSound* soundFile;  /**< Fichier audio */
    static const QString type;
public:

    Sound() : soundFile(new QSound(filename)){}

    const QSound& getSound() const; /**<  Accesseur de l'attribut soundFile */
    const QString& getType() const;
    void setFilename(const QString&);
    NoteInterface* getUI() const;
};

#endif // SOUND_H
