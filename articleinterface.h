#ifndef ARTICLEINTERFACE_H
#define ARTICLEINTERFACE_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QObject>
#include "notes/article.h" // inclusion récursif.?

class Article;

class ArticleInterface: public QWidget{
    Q_OBJECT
    Article* article;
    QLineEdit* titleEdit;
    QTextEdit* textEdit;
    QFormLayout* layout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* mainLayout;
    QPushButton* generate;
public:
    ArticleInterface(Article* a,QWidget *parent = 0);
public slots:
    void save();
};

#endif // ARTICLEINTERFACE_H
