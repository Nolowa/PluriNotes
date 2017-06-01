#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QPushButton>
#include <QMap>
#include <QModelIndex>
#include <QUuid>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "notesmanager.h"
#include "noteslistview.h"

class Sidebar : public QWidget
{
    Q_OBJECT

    NotesManager& nm;

    QVBoxLayout* layout;

    NotesListView* stdListview;
    NotesListView* binListview;

    QHBoxLayout* btnsLayout;
    QPushButton** buttons;
    QLabel* binTitle;

    QPushButton* deleteBtn;

    void initUI();

public:
    explicit Sidebar(NotesManager& nm, QWidget *parent = 0);

signals:
    void noteSelected(const NoteHolder*);
public slots:

};

#endif // SIDEBAR_H