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

class Article: public Note{
    QString text;
    static const QString type;
public:
    Article(QUuid identifier);
    void setText(const QString& texte);
    const QString& getText() const;
    ArticleInterface* getInterface();

    Article(const Article& a):Note(a),text(a.getText()){}

    void load(Note* n);
    Note* save();

    const QString& getType() const;
};

#endif // ARTICLE_H
