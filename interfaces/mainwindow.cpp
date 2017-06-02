#include "mainwindow.h"


MainWindow::MainWindow(NotesManager& nm, RelationsManager<NoteHolder>& rm, MementoCaretaker& mement, QWidget *parent) : QMainWindow(parent),memento(&mement)

{
    mf = new Mainframe(nm);

    setCentralWidget(mf);

    relationsView = new RelatedDockView(rm,*memento);
    relationsDock = new QDockWidget("Relations", this);
    relationsDock->setAllowedAreas(Qt::RightDockWidgetArea);
    relationsDock->setWidget(relationsView);
    relationsDock->setFeatures(QDockWidget::DockWidgetClosable);

    connect(mf->getSidebar(), SIGNAL(noteSelected(const NoteHolder*)), relationsView, SLOT(setSelectedNote(const NoteHolder*)));

    addDockWidget(Qt::RightDockWidgetArea, relationsDock);
    setWindowTitle("PluriNotes");
    setWindowIcon(QIcon(":/icons/article"));

    initMenu();

    //mémento
    connect(&nm, SIGNAL(noteStatusChangedwithState(const NoteHolder&,NoteState,NoteState)), memento, SLOT(saveMementoState(const NoteHolder&,NoteState,NoteState)));
    connect(memento,SIGNAL(changeNoteState(const NoteHolder&, NoteState)) ,&nm,SLOT(noteStatusChangeRequestedFromMemento(const NoteHolder&, NoteState)));
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
     relationsDock->toggleViewAction()->setShortcut(QKeySequence("Ctrl+R"));
     menuAffichage->addAction(relationsDock->toggleViewAction());

     QObject::connect(actionUndo, SIGNAL(triggered()), memento, SLOT(undo()));
     QObject::connect(actionRedo, SIGNAL(triggered()), memento, SLOT(redo()));


}

