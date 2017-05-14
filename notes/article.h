#ifndef ARTICLE_H
#define ARTICLE_H


#include "note.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QWidget>
#include <QLabel>
#include "articleinterface.h" // inclusion récursif.?
class ArticleInterface;

class Article: public Note{
    QString text;

public:
    Article(QUuid identifier);
    void setText(const QString& texte);
    const QString& getText() const;
<<<<<<< HEAD:article.h
    ArticleInterface* getInterface();
=======
    Article(const Article& a):Note(a),text(a.getText()){}
    void load(Note* n);
    Note* save();
>>>>>>> 9cb9ff33adb691c711ec2803bd079498782ea2ac:notes/article.h
};

#endif // ARTICLE_H
