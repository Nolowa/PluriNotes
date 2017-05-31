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
#include "relations/relationsmanager.h"


class MainWindow : public QMainWindow
{
    Mainframe* mf;
    RelatedDockView* relationsView;
    QDockWidget* relationsDock;

    //menu
    QMenu* menuFichier;
    QMenu* menuEdition;
    QMenu* menuAffichage;
    QAction* actionRelation;

    void initMenu();

    Q_OBJECT

public:
    explicit MainWindow(NotesManager& nm, RelationsManager<NoteHolder>& rm, QWidget *parent = 0);

signals:

public slots:

};

#endif // MAINWINDOW_H
