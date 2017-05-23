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
#include <QComboBox>
#include "notes/article.h"
#include "noteinterface.h"

class Article;

class ArticleInterface: public NoteInterface{
    Q_OBJECT
    const Article* article;
    QLineEdit* titleEdit;
    QLineEdit* idEdit;
    QTextEdit* textEdit;
    QFormLayout* layout;
    QHBoxLayout* buttonLayout;
    QHBoxLayout* boxLayout;
    QHBoxLayout* buttonLayoutc;
    QVBoxLayout* mainLayout;
    QPushButton* generate;
    QComboBox * versions;
    QPushButton* choisir;
public:
    ArticleInterface(const Article& a, QWidget *parent = 0);
    void parcourir();
public slots:
    void save();
    void charger();
};

#endif // ARTICLEINTERFACE_H
