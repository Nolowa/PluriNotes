#include "articleinterface.h"
#include <iostream>
#include <QDateTime>
#include <QSql>
#include <QDebug>
#include <QSqlQuery>
#include <QStringList>
ArticleInterface::ArticleInterface(const Article& a, QWidget *parent): NoteInterface(parent),article(&a){
    layout=new QFormLayout;
    buttonLayout=new QHBoxLayout;
    buttonLayoutc=new QHBoxLayout;
    boxLayout=new QHBoxLayout;
    mainLayout= new QVBoxLayout;
    choisir=new QPushButton(QString("choisir"));
    generate= new QPushButton(QString("sauvegarder"));
    titleEdit= new QLineEdit(article->getTitle(),this);
    textEdit= new QTextEdit(article->getText(),this);
    idEdit= new QLineEdit(article->getIdentifier().toString(),this);
    idEdit->setReadOnly(1);
    versions=new QComboBox;
    //ajustement de la taille des Widgets
    titleEdit->setFixedWidth(180);
    idEdit->setFixedWidth(300);

    //ajout des widgets à la layout
    layout->addRow("Identifiant :",idEdit);
    layout->addRow("Titre :",titleEdit);
    layout->addRow("Corps :",textEdit);
    buttonLayout->addStretch();
    buttonLayout->addWidget(generate);
    buttonLayout->addStretch();
    boxLayout->addStretch();
    boxLayout->addWidget(versions);
    boxLayout->addStretch();
    buttonLayoutc->addStretch();
    buttonLayoutc->addWidget(choisir);
    buttonLayoutc->addStretch();
    parcourir();
    //gestion des layouts
    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(boxLayout);
    mainLayout->addLayout(buttonLayoutc);
    //layout->addWidget(generate);

    setLayout(mainLayout);
    setWindowTitle("Article");

    //slot
    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(choisir, SIGNAL(clicked()), this, SLOT(charger()));
}

void ArticleInterface::parcourir(){
    QSqlQuery q1;
    q1.prepare("SELECT n.Id,n.Title,n.Edited FROM (Note n INNER JOIN Article a ON n.Id=a.Id);");
    q1.bindValue(":Id",article->getIdentifier());
    if (!q1.exec()) {
          std::cout<<"erreur"<<std::endl;
    }else{
        while (q1.next()) {
                QString Id = q1.value(0).toString();
                QString Title = q1.value(1).toString();
                QString Edited = q1.value(2).toString();
                QString final;
                final+=Id;final+=" ";final+=Title;final+=Edited;
                QStringList s;
                s<<final;
                versions->addItems(s);
            }
    }
    q1.finish();
}

//slot
void ArticleInterface::save(){
    Article * a = new Article(*article);
    a->setText(textEdit->toPlainText());
    a->setTitle(titleEdit->text());

    article = a;
    emit newVersion(a); // signal d'émition pour la création d'une nouvelle version
    //QMessageBox::information(this, "Fichier", "Enregisterment de :\n" +titleEdit->text() +"\n"+ textEdit->toPlainText());

}

void ArticleInterface::charger(){

}
