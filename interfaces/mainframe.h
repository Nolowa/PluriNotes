#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QWidget>
#include "noteslistview.h"
#include "notesmanager.h"
#include "noteframeview.h"

class Mainframe : public QWidget
{
    Q_OBJECT

    NotesManager& data;

    NotesListView* listView;
    NoteFrameView* noteView;

    void initUI();
public:
    explicit Mainframe(NotesManager& nm, QWidget *parent = 0);

signals:

public slots:

};

#endif // MAINFRAME_H
