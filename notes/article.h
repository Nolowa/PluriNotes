#ifndef ARTICLE_H
#define ARTICLE_H


#include "note.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QWidget>
#include <QLabel>
#include "interfaces/articleinterface.h"
class ArticleInterface;

/*! Classe Article, classe fille de Note  */

class Article: public Note{
    QString text; /**< Texte qui correspond au coeur de l'article  */
    static const QString type;
public:
    Article(QUuid identifier); /**< Constructeur */
    void setText(const QString& texte); /**< Méthode modifiant l'attribut text */
    const QString& getText() const; /**< Accesseur de l'attribut Text */
    ArticleInterface* getInterface(); /**< Méthode virtuelle renvoyant l'interface de Article */

    Article(const Article& a):Note(a),text(a.getText()){} /**< Constructeur de recopie */

    void load(Note* n);
    Note* save();

    const QString& getType() const;
};

#endif // ARTICLE_H
