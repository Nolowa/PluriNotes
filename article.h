#ifndef ARTICLE_H
#define ARTICLE_H


#include "note.h"

class Article: public Note{
    QString text;
public:
    Article(QUuid identifier);
};

#endif // ARTICLE_H
