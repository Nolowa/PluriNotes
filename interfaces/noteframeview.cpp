#include "noteframeview.h"
#include "notes/note.h"
#include <QHBoxLayout>
#include <QObject>

NoteFrameView::NoteFrameView(QWidget *parent) : QWidget(parent), widget(nullptr)
{
    initUI();
}

void NoteFrameView::initUI(){
    setMinimumWidth(500);
    layout = new QHBoxLayout();
    setLayout(layout);

}

void NoteFrameView::setNote(const Note * note){
    if(widget != nullptr){
        layout->removeWidget(widget);
        delete widget;
    }

    widget = note->getUI();
    layout->addWidget(widget);

    QObject::connect(widget, SIGNAL(newVersion(const Note*)), this, SIGNAL(noteUpdated(const Note*)));
}

void NoteFrameView::setNoteArchive(const Note * note){
    if(widget != nullptr){
        layout->removeWidget(widget);
        delete widget;
    }

    widget = note->getUIarchive();
    layout->addWidget(widget);

    QObject::connect(widget, SIGNAL(newVersion(const Note*)), this, SIGNAL(noteUpdated(const Note*)));
}
