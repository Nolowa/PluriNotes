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
#include <QTabWidget>

#include "notesmanager.h"
#include "noteslistview.h"
#include "notes/noteholder.h"

class Sidebar : public QWidget
{
    Q_OBJECT

    NotesManager& nm;

    QVBoxLayout* layout;

    QTabWidget* tabs;

    NotesListView* stdListview;
    NotesListView* binListview;
    NotesListView* tskListview;


    QHBoxLayout* btnsLayout;
    QPushButton** buttons;
    QLabel* binTitle;

    QPushButton* deleteBtn;
    QPushButton* restoreBtn;

    const NoteHolder* selectedNote = nullptr;

    void initUI();
    void selectNote(const NoteHolder*);

public:
    explicit Sidebar(NotesManager& nm, QWidget *parent = 0);

signals:
    void noteSelected(const NoteHolder*);
    void noteStatusChangeRequested(const NoteHolder&, NoteState newState);
public slots:
    void deleteNote();
    void restoreNote();
    void selectActiveNote(const NoteHolder*);
    void selectDeletedNote(const NoteHolder*);

};

#endif // SIDEBAR_H
