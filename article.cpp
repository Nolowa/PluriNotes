#include "article.h"

Article::Article(QUuid identifier):Note(identifier),text(QString("")){}

void Article::setText(const QString& texte){
    text=texte;
    setEdited();
}

const QString& Article::getText() const{
    return text;
}
