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
    ArticleInterface* getInterface();
};

#endif // ARTICLE_H
