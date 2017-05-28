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
#include <QVector>
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
    /**< la partie choisir et charger les versions */
    QComboBox * versions;
    QPushButton* choisir;
    int Id;
    std::vector <int> a;

    QPushButton* activer;/**< archive->active */
    QPushButton* supprimer;/**< supprimer */
    QHBoxLayout* buttonLayouts;
public:
    ArticleInterface(const Article& a, QWidget *parent = 0);
    ArticleInterface(const Article& a,int i, QWidget *parent = 0);/**< l'interface pour les notes non éditable */
    void parcourir();/**< parcourir les versions*/

public slots:
    void save();
    void charger();/**< charger la version*/
    void enregistrerid(int i);/**< garder id présent*/

};

#endif // ARTICLEINTERFACE_H
