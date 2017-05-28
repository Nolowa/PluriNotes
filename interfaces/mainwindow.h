#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include "mainframe.h"
#include "notesmanager.h"
#include "relateddockview.h"
#include "relations/relationsmanager.h"

class MainWindow : public QMainWindow
{
    Mainframe* mf;
    RelatedDockView* relationsView;
    QDockWidget* relationsDock;

    Q_OBJECT
public:
    explicit MainWindow(NotesManager& nm, RelationsManager<Note>& rm, QWidget *parent = 0);

signals:

public slots:
};

#endif // MAINWINDOW_H
