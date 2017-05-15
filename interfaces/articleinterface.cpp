#include "articleinterface.h"
#include <QMessageBox>

ArticleInterface::ArticleInterface(Article *a, QWidget *parent): QWidget(parent),article(a){
    layout=new QFormLayout;
    buttonLayout=new QHBoxLayout;
    mainLayout= new QVBoxLayout;
    generate= new QPushButton(QString("sauvegarder"));
    titleEdit= new QLineEdit(article->getTitle(),this);
    textEdit= new QTextEdit(article->getText(),this);
    idEdit= new QLineEdit(article->getIdentifier().toString(),this);
    idEdit->setReadOnly(1);

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

    //gestion des layouts
    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttonLayout);
    //layout->addWidget(generate);

    setLayout(mainLayout);
    setWindowTitle("Article");

    //slot
    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(save()));

}

//slot
void ArticleInterface::save(){
    article->setText(textEdit->toPlainText());
    article->setTitle(titleEdit->text());
    //QMessageBox::information(this, "Fichier", "Enregisterment de :\n" +titleEdit->text() +"\n"+ textEdit->toPlainText());

}
