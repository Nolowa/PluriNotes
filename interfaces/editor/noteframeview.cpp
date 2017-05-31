#include "noteframeview.h"
#include "notes/noteholder.h"
#include <QHBoxLayout>
#include <QObject>
#include <QFrame>

NoteFrameView::NoteFrameView(QWidget *parent) :
    QWidget(parent),
    widget(nullptr)
{
    initUI();
}

void NoteFrameView::initUI(){


    layout = new QVBoxLayout;
    btns_bar = new QWidget;
    btns_bar_l = new QHBoxLayout;


    save_btn = new QPushButton("Enregistrer");
    copy_id_btn = new QPushButton("Référencer");
    delete_btn = new QPushButton("Supprimer");

    btns_bar_l->addWidget(save_btn);
    btns_bar_l->addWidget(copy_id_btn);
    btns_bar_l->addSpacing(10);
    btns_bar_l->addWidget(delete_btn);

    btns_bar->setMaximumHeight(50);
    btns_bar->setLayout(btns_bar_l);
    btns_bar->setVisible(false);

    layout->addWidget(btns_bar);

    setMinimumWidth(500);
    setLayout(layout);

    QObject::connect(save_btn, SIGNAL(pressed()), this, SLOT(save()));

}

void NoteFrameView::setNote(const NoteHolder * note){
    this->note = note;

    if(widget != nullptr){
        layout->removeWidget(widget);
        delete widget;
    }

    btns_bar->setVisible(true);
    save_btn->setVisible(note->isActive());
    delete_btn->setVisible(!note->isDeleted());

    widget = note->getLastVersion().getUI();
    layout->insertWidget(0, widget);
}

void NoteFrameView::save(){
    if(widget){
        const Note& newBody = widget->toNote();
        emit noteSaved(*note, newBody);
    }
}
