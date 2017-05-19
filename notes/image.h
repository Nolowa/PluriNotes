#ifndef IMAGE_H
#define IMAGE_H

#include <QFile>
#include <QImage>
#include "notextualnote.h"
#include "interfaces/imageinterface.h"

class ImageInterface;
/*! Classe Image, classe fille de NoTextualNote */

class Image: public NoTextualNote {
    QImage image; /**< Fichier image */
    QString nameFile; /**< URL du fichier image */
    static const QString type;
public:
    Image(QUuid identifier = QUuid::createUuid()); /**< Constructeur */
    Image(QUuid identifier,QDateTime c);
    void setImage(const QString& im);  /**< Méthode modifiant les deux attributs nameFile et image */
    const QString& getnameFile() const; /**< Accesseur de l'attribut nameFile */
    const QImage& getImage() const; /**< Accesseur de l'attribut image  */
    const QImage& getFile() const; /**< Accesseur de l'attribut image */
    QWidget* getUI() const; /**< Méthode virtuelle renvoyant l'interface de Image */


    Note* save();
    void load(Note* n);

const QString& getType() const;
};

#endif // IMAGE_H
