#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QWidget>
#include "noteslistview.h"
#include "notesmanager.h"
#include "noteframeview.h"
#include "corbeillelistview.h"

class Mainframe : public QWidget
{
    Q_OBJECT

    NotesManager& data;

    NotesListView* listView;
    NoteFrameView* noteView;
    CorbeilleListView* CorbeilleView;//pour corbeille
    Corbeille& cb;//pour corbeille

    void initUI();
public:
    //explicit Mainframe(NotesManager& nm, QWidget *parent = 0);
    explicit Mainframe(NotesManager& nm,Corbeille& cb ,QWidget *parent = 0);//pour corbeille

signals:

public slots:

};

#endif // MAINFRAME_H
