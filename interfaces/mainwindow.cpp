#include "mainwindow.h"

MainWindow::MainWindow(NotesManager& nm, RelationsManager<Note>& rm, QWidget *parent) : QMainWindow(parent)
{

    mf = new Mainframe(nm);
    setCentralWidget(mf);

    relationsView = new RelatedDockView(rm);
    relationsDock = new QDockWidget("Relations", this);
    relationsDock->setAllowedAreas(Qt::RightDockWidgetArea);
    relationsDock->setWidget(relationsView);
    relationsDock->setFeatures(QDockWidget::DockWidgetClosable);

    connect(mf->getListView(), SIGNAL(noteSelected(const Note*)), relationsView, SLOT(setSelectedNote(const Note*)));

    addDockWidget(Qt::RightDockWidgetArea, relationsDock);
    setWindowTitle("PluriNotes");
    setWindowIcon(QIcon(":/icons/article"));

    initMenu();


}


void MainWindow::initMenu(){

    // Menu
    menuFichier = menuBar()->addMenu("&Fichier");

    //Quitter
    QAction* actionQuitter = new QAction("Quitter", this);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    //actionQuitter->setIcon(QIcon(":/icons/iconeQuitter")); // plante
    menuFichier->addAction(actionQuitter);



    //Autre fonctionnalité du menu Fichier...
    QAction* autreAction = new QAction("Fonctionnalité à définir", this);
    menuFichier->addAction(autreAction);

    //Menu EDITION
    menuEdition = menuBar()->addMenu("&Edition");

     //Undo
     QAction* actionUndo = new QAction("Annuler", this);
     menuEdition->addAction(actionUndo);
     actionUndo->setShortcut(QKeySequence("Ctrl+Z"));

     //Redo
     QAction* actionRedo = new QAction("Rétablir", this);
     menuEdition->addAction(actionRedo);
     actionRedo->setShortcut(QKeySequence("Ctrl+Y"));

     //Menu AFFICHAGE
     menuAffichage = menuBar()->addMenu("&Affichage");

     //Affichage pour la partie Relation rétractable.
     actionRelation = new QAction("Afficher les relations");
     actionRelation->setCheckable(true);
     actionRelation->setChecked(true);
     actionRelation->setShortcut(QKeySequence("Ctrl+R"));
     //connect(actionAfficherDockDroit, SIGNAL(toggled(bool)), this, SLOT(showRelation(bool)));

     menuAffichage->addAction(actionRelation);



}
