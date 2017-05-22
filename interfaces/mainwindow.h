#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainframe.h"
#include "notesmanager.h"

class MainWindow : public QMainWindow
{
    Mainframe* mf;
    Q_OBJECT
public:
    explicit MainWindow(NotesManager& nm, QWidget *parent = 0);

signals:

public slots:
};

#endif // MAINWINDOW_H
