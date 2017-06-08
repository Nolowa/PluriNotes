#include "mainwindow.h"
#include "notes/noteholder.h"


MainWindow::MainWindow(NotesManager& nm, RelationsManager<NoteHolder>& rm, MementoCaretaker& mement, Database& db, QWidget *parent) : QMainWindow(parent), notesManager(nm), database(db), relationsManager(rm), relationsProxy(new NotesRelationsManagerSlotsProxy(rm)), memento(&mement)
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


    addDockWidget(Qt::RightDockWidgetArea, relationsDock);
    addDockWidget(Qt::RightDockWidgetArea, versionsDock);

    setWindowTitle("PluriNotes");
    setWindowIcon(QIcon(":/icons/article"));

    initUI();

    /*******************************************mémento*******************************************/
    //Memento ListView
    connect(&nm, SIGNAL(noteStatusChanged(const NoteHolder&, NoteState)), memento, SLOT(saveMementoState(const NoteHolder&,NoteState)));
    connect(memento,SIGNAL(changeNoteState(const NoteHolder&, NoteState)) ,&nm,SLOT(noteStatusChangeRequested(const NoteHolder&, NoteState)));
    connect(&nm, SIGNAL(noteStatusChanged(NoteHolder, NoteState)), relationsView, SLOT(noteStatusChanged(NoteHolder)));
    connect(&nm, SIGNAL(noteStatusChanged(NoteHolder, NoteState)), versionsView, SLOT(noteStatusChanged(NoteHolder)));
    connect(&nm, SIGNAL(noteStatusChanged(NoteHolder, NoteState)), mf->getNoteView(), SLOT(noteStatusChanged(NoteHolder)));

    //Memento Relation
    connect(relationsView,SIGNAL(linkCreated(QString, const NoteHolder&, const NoteHolder&,QString)),memento,SLOT(saveMementoRelation( QString,const NoteHolder&, const NoteHolder&, QString)));
    connect(relationsView,SIGNAL(linkDestroyed(QString, const NoteHolder&, const NoteHolder&,QString)),memento,SLOT(saveMementoRelation( QString,const NoteHolder&, const NoteHolder&, QString)));

    /* Manque le connect du retour*/
    connect(memento,SIGNAL(DeleteRelation(const QString&,const NoteHolder&,const NoteHolder&)), relationsProxy, SLOT(unlink(const QString&,const NoteHolder&,const NoteHolder&)));
    connect(memento,SIGNAL(CreateRelation(const QString&,const NoteHolder&,const NoteHolder&,const QString&)), relationsProxy, SLOT(link(const QString&,const NoteHolder&,const NoteHolder&, const QString&)));
    /* Manque le connect du retour*/

}


void MainWindow::initUI(){

    // Menu
    menuFichier = menuBar()->addMenu("&Fichier");

    //Quitter
    QAction* actionQuitter = new QAction("Quitter", this);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    //actionQuitter->setIcon(QIcon(":/icons/iconeQuitter")); // plante
    menuFichier->addAction(actionQuitter);



    //Autre fonctionnalité du menu Fichier...
    QAction* autreAction = new QAction("Menu d'aide", this);
    menuFichier->addAction(autreAction);
    autreAction->setShortcut(QKeySequence("Ctrl+M"));
    helpingMenu= new QMessageBox(this);
    helpingMenu->setIcon(QMessageBox::Information);
    helpingMenu->setText("Menu d'aide");
    helpingMenu->setInformativeText(" ctrl+M : Menu d'aide \n ctrl+Z : Annuler \n ctrl+Y : Rétablir \n ctrl+R : Afficher/Enlever la vue des relations \n ctrl+V : Afficher/Enlever  la vue des versions  \n ctrl+Q : Quitter l’application");
    helpingMenu->addButton("Quitter", QMessageBox::RejectRole);



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


    //Corbeille
     relationsDock->toggleViewAction()->setShortcut(QKeySequence("Ctrl+R"));
     versionsDock->toggleViewAction()->setShortcut(QKeySequence("Ctrl+V"));

     menuAffichage->addAction(relationsDock->toggleViewAction());
     menuAffichage->addAction(versionsDock->toggleViewAction());

     emptyTrashDialog = new QMessageBox(this);
     emptyTrashDialog->setIcon(QMessageBox::Warning);
     emptyTrashDialog->setText("Voulez-vous vider la corbeille avant de quitter ?");
     emptyTrashDialog->setInformativeText("La corbeille contient les notes que vous avez supprimés. Une fois la corbeille vidée, vous ne pourrez plus les récupérer.");
     emptyTrashDialog->setModal(true);
     emptyTrashDialog->setWindowModality(Qt::WindowModal);
     emptyTrashDialog->addButton("Ne pas vider", QMessageBox::RejectRole);
     emptyTrashDialog->addButton("Vider la corbeille", QMessageBox::DestructiveRole);


     QObject::connect(actionUndo, SIGNAL(triggered()), memento, SLOT(undo()));
     QObject::connect(actionRedo, SIGNAL(triggered()), memento, SLOT(redo()));
     QObject::connect(emptyTrashDialog, SIGNAL(accepted()), &database, SLOT(emptyTrash()));
     QObject::connect(autreAction, SIGNAL(triggered()),helpingMenu,SLOT(show()));

}

void MainWindow::closeEvent(QCloseEvent *event){
    Q_UNUSED(event);

    NotesManager::Iterator it = notesManager.getIterator();

    // Si il y a au moins une note supprimé (dans la corbeille), on propose à l'utilisateur de vider la corbeille
    while(!it.isDone()){
        it.next();
        const NoteHolder& holder = it.current();
        if(holder.isDeleted()){
            emptyTrashDialog->exec();
            return;
        }
    }
}

