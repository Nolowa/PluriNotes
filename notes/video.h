#ifndef VIDEO_H
#define VIDEO_H

#include "notes/notextualnote.h"
#include <QVideoWidget>
#include <QMovie>


class VideoInterface;

/*! Classe Video, classe fille de NoTextualNote*/
class Video: public NoTextualNote{
    QMovie * videoFile; /**< File vidéo */
    QString nameVideoFile; /**< URL du fichier vidéo */
    static const QString type;

public:
    Video(QUuid identifier = QUuid::createUuid());
    Video(QUuid identifier,const QString& filename=""); /**< Constructeur*/
    Video(QUuid identifier,QDateTime c,const QString& filename);

    NoteInterface* getUI() const;  /**< Méthode virtuelle renvoyant l'interface de la Video */
    NoteInterface* getUIarchive() const;
    const QString& getVideoFileName() const;  /**< Accesseur de l'attribut nameVideoFile */
    const QMovie& getVideo() const; /**< Accesseur de l'attribut videoFile */
    // change nameVideoFile et videoFile
    void setVideoFile(const QString& name); /**< Méthode modifiant les attributs videoFile et nameVideoFile */

    const QString& getType() const;
};

#endif // VIDEO_H
