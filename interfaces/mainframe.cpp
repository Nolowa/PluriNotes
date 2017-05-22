#include "mainframe.h"
#include "notesmanager.h"
#include <QHBoxLayout>

Mainframe::Mainframe(NotesManager& nm, QWidget *parent) : QWidget(parent), data(nm){
    initUI();
    show();

}

void Mainframe::initUI(){



    listView = new NotesListView(data, this);
    noteView = new NoteFrameView(this);


    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(listView);
    layout->addWidget(noteView);

    layout->setMargin(0);
    layout->setSpacing(0);

    setLayout(layout);

    connect(listView, SIGNAL(noteSelected(const Note *)), noteView, SLOT(setNote(const Note*)));
    connect(noteView, SIGNAL(noteUpdated(const Note *)), &data, SLOT(updateNote(const Note *)));




}
