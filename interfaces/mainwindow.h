#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QtWidgets>
#include "mainframe.h"
#include "notesmanager.h"
#include "interfaces/relations/relateddockview.h"
#include "interfaces/versions/versionsdockview.h"
#include "relations/relationsmanager.h"
#include "memento.h"


class MainWindow : public QMainWindow
{
    Mainframe* mf;

    NotesManager& notesManager;
    Database& database;

    RelatedDockView* relationsView;
    QDockWidget* relationsDock;

    VersionsDockView* versionsView;
    QDockWidget* versionsDock;

    RelationsManager<NoteHolder>& relationsManager;
    NotesRelationsManagerSlotsProxy* relationsProxy;

    MementoCaretaker* memento;

    //menu
    QMenu* menuFichier;
    QMenu* menuEdition;
    QMenu* menuAffichage;
    QAction* actionRelation;

    QMessageBox* emptyTrashDialog;
    QMessageBox* helpingMenu;

    void initUI();
    void initMemento();
    void closeEvent(QCloseEvent *event);

    Q_OBJECT

public:
    explicit MainWindow(NotesManager& nm, RelationsManager<NoteHolder>& rm, MementoCaretaker& mement, Database& db, QWidget *parent = 0);

    RelatedDockView* getRelatedDockView() { return relationsView; }
signals:
    void undo();
    void redo();

};

#endif // MAINWINDOW_H
