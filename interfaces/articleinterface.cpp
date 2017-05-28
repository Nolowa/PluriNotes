#include "articleinterface.h"

ArticleInterface::ArticleInterface(const Article& a, QWidget *parent): NoteInterface(parent),article(&a){
    layout=new QFormLayout;
    buttonLayout=new QHBoxLayout;
    buttonLayoutc=new QHBoxLayout;
    buttonLayouts=new QHBoxLayout;
    boxLayout=new QHBoxLayout;
    mainLayout= new QVBoxLayout;
    choisir=new QPushButton(QString("choisir"));
    generate= new QPushButton(QString("sauvegarder"));
    supprimer= new QPushButton(QString("supprimer"));
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
    buttonLayouts->addStretch();
    buttonLayouts->addWidget(supprimer);
    buttonLayouts->addStretch();
    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(boxLayout);
    mainLayout->addLayout(buttonLayoutc);
    mainLayout->addLayout(buttonLayouts);
    //layout->addWidget(generate);

    setLayout(mainLayout);
    setWindowTitle("Article");

    //slot
    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(versions, SIGNAL(activated(int)), this, SLOT(enregistrerid(int)));
    QObject::connect(choisir, SIGNAL(clicked()), this, SLOT(charger()));
    //QObject::connect(choisir, SIGNAL(clicked()), this, SLOT(supprimer());
}

ArticleInterface::ArticleInterface(const Article& a,int i, QWidget *parent): NoteInterface(parent),article(&a){
    layout=new QFormLayout;
    buttonLayout=new QHBoxLayout;
    buttonLayoutc=new QHBoxLayout;
    mainLayout= new QVBoxLayout;
    activer= new QPushButton(QString("activer"));

    titleEdit= new QLineEdit(article->getTitle(),this);
    titleEdit->setReadOnly(1);
    textEdit= new QTextEdit(article->getText(),this);
    textEdit->setReadOnly(1);
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
    buttonLayout->addWidget(activer);
    buttonLayout->addStretch();


    //gestion des layouts
    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Article");

    //slot

    //QObject::connect(activer, SIGNAL(clicked()), this, SLOT(charger()));
}

void ArticleInterface::parcourir(){
    QSqlQuery q;
    q.exec("SELECT n.Id,n.Title,n.Edited FROM (Note n INNER JOIN Article a ON n.Id=a.Id) WHERE a.Idreal='"+ article->getIdentifier().toString()+"';");
    while (q.next()) {
        a.push_back(q.value(0).toInt());
        QString final;
        final=q.value(0).toString()+"| "+q.value(1).toString()+q.value(2).toString();
        QStringList s;
        s<<final;
        versions->addItems(s);
    }
    q.finish();
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
    QSqlQuery q;
    q.exec("SELECT n.Title,a.Text FROM Article a,Note n WHERE n.Id=a.Id AND a.Id='"+ QString::number(Id) +"';");
    q.next();
    QString Title1=q.value(0).toString();
    QString Text=q.value(1).toString();
    Article* change=const_cast<Article*>(article);
    change->setTitle(Title1);
    change->setText(Text);

}

void ArticleInterface::enregistrerid(int i){
    std::cout<<i;
    Id=a[i];
    std::cout<<Id;
}


