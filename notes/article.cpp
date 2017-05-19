#include "article.h"
#include <QFile>
#include <QTextCodec>
#include <QMessageBox>
const QString Article::type = QString("Article");

Article::Article(QUuid identifier):Note(identifier),text(QString("")){
}

Article::Article(QUuid identifier, QDateTime c):Note(identifier,c),text(QString("")){}

void Article::setText(const QString& texte){
    text=texte;
    setEdited();
}

const QString& Article::getText() const{
    return text;
}

QWidget* Article::getUI() const{
    return new ArticleInterface(*this);

}


void Article::load(Note* n){
    Article* nouveau;
    nouveau=static_cast<Article*>(n);
    this->setTitle(nouveau->getTitle());
    this->setCreated(nouveau->getCreated());
    this->setEdited(QDateTime::currentDateTime());
    this->setState(nouveau->getStates());
    this->setText(nouveau->getText());
}

Note* Article::save(){
    Note* n=new Article(*this);
    return n;
}

const QString& Article::getType() const{
    return type;
}
