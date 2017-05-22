#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QtWidgets>
#include "mainframe.h"
#include "notesmanager.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
    Mainframe* mf;

    //menu
    QMenu* menuFichier;
    QMenu* menuEdition;
    QMenu* menuAffichage;
    QAction* actionRelation;

    void initMenu();

public:
    explicit MainWindow(NotesManager& nm, QWidget *parent = 0);

signals:

public slots:
    //void showRelation(bool); // pour l'affichage de la partie rectractable
};

#endif // MAINWINDOW_H
