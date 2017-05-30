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
#include "relateddockview.h"
#include "relations/relationsmanager.h"
#include "memento.h"


class MainWindow : public QMainWindow
{
    Mainframe* mf;
    RelatedDockView* relationsView;
    QDockWidget* relationsDock;
    MementoCaretaker* memento;


    //menu
    QMenu* menuFichier;
    QMenu* menuEdition;
    QMenu* menuAffichage;
    QAction* actionRelation;

    void initMenu();

    Q_OBJECT

public:


    explicit MainWindow(NotesManager& nm, RelationsManager<Note>& rm,MementoCaretaker& mement,Corbeille& cb, QWidget *parent = 0);


signals:
    void undo();
    void redo();
public slots:
    //void showRelation(bool); // pour l'affichage de la partie rectractable
};

#endif // MAINWINDOW_H
