#include "mainwindow.h"


MainWindow::MainWindow(NotesManager& nm, RelationsManager<NoteHolder>& rm, MementoCaretaker& mement, Database& db, QWidget *parent) : QMainWindow(parent),memento(&mement)
{
    mf = new Mainframe(nm);

    setCentralWidget(mf);

    relationsView = new RelatedDockView(rm,*memento);
    relationsDock = new QDockWidget("Relations", this);
    relationsDock->setAllowedAreas(Qt::RightDockWidgetArea);
    relationsDock->setWidget(relationsView);
    relationsDock->setFeatures(QDockWidget::DockWidgetClosable);

    versionsView = new VersionsDockView(&db, mf->getNoteView());
    versionsDock = new QDockWidget("Historique des versions", this);
    versionsDock->setAllowedAreas(Qt::RightDockWidgetArea);
    versionsDock->setWidget(versionsView);
    versionsDock->setFeatures(QDockWidget::DockWidgetClosable);

    connect(mf->getSidebar(), SIGNAL(noteSelected(const NoteHolder*)), relationsView, SLOT(setSelectedNote(const NoteHolder*)));
    connect(mf->getSidebar(), SIGNAL(noteSelected(const NoteHolder*)), versionsView, SLOT(setCurrentNote(const NoteHolder*)));
    connect(&nm, SIGNAL(noteStatusChanged(NoteHolder)), relationsView, SLOT(noteStatusChanged(NoteHolder)));
    connect(&nm, SIGNAL(noteStatusChanged(NoteHolder)), versionsView, SLOT(noteStatusChanged(NoteHolder)));
    connect(&nm, SIGNAL(noteStatusChanged(NoteHolder)), mf->getNoteView(), SLOT(noteStatusChanged(NoteHolder)));

    addDockWidget(Qt::RightDockWidgetArea, relationsDock);
    addDockWidget(Qt::RightDockWidgetArea, versionsDock);

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
     versionsDock->toggleViewAction()->setShortcut(QKeySequence("Ctrl+V"));

     menuAffichage->addAction(relationsDock->toggleViewAction());
     menuAffichage->addAction(versionsDock->toggleViewAction());

     QObject::connect(actionUndo, SIGNAL(triggered()), memento, SLOT(undo()));
     QObject::connect(actionRedo, SIGNAL(triggered()), memento, SLOT(redo()));


}

