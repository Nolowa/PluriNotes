#ifndef ARTICLE_H
#define ARTICLE_H


#include "note.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QWidget>
#include <QLabel>

class Article: public Note{
    QString text;

public:
    Article(QUuid identifier);
    void setText(const QString& texte);
    const QString& getText() const;
    Article(const Article& a):Note(a),text(a.getText()){}
    void load(Note* n);
    Note* save();
};

#endif // ARTICLE_H
