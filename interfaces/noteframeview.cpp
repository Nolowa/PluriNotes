#include "noteframeview.h"
#include "notes/note.h"
#include <QHBoxLayout>

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
}
