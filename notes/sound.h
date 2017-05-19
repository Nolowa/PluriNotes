#ifndef SOUND_H
#define SOUND_H

#include "notes/notextualnote.h"
#include <QSound>
#include "interfaces/soundinterface.h"
class SoundInterface;

/*! Classe Sound, classe fille de NoTextualNote*/
class Sound: public NoTextualNote{
    QSound* soundFile;  /**< Fichier audio */
    QString soundFileName; /**< URL du fichier audio */
    static const QString type;
public:
    Sound(QUuid identifier,const QString& filename=""); /**< Constructeur */
    Sound(QUuid identifier,QDateTime c,const QString& filename);
    SoundInterface* getInterface(); /**< Méthode virtuelle renvoyant l'interface de Sound */

    const QSound& getSound() const; /**<  Accesseur de l'attribut soundFile */
    const QString& getSoundFileName() const; /**<  Accesseur de l'attribut soudFileName */
    void setSoundFile(const QString& name);/**< Méthode modifiant les attributs soundFile et soundFileName */

    const QString& getType() const;

    QWidget* getUI() const;

};

#endif // SOUND_H
