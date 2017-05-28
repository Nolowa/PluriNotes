#include "mainframe.h"
#include "notesmanager.h"
#include <QHBoxLayout>

/*Mainframe::Mainframe(NotesManager& nm, QWidget *parent) : QWidget(parent), data(nm){
    initUI();
    show();

}*/

void Mainframe::initUI(){



    listView = new NotesListView(data, this);
    noteView = new NoteFrameView(this);
    CorbeilleView=new CorbeilleListView(cb,this);//pour corbeille

    //QHBoxLayout* layout = new QHBoxLayout;

    //layout->addWidget(listView);
    //layout->addWidget(noteView);

    //layout->setMargin(0);
    //layout->setSpacing(0);

    //setLayout(layout);

    QGridLayout* mainLayout = new QGridLayout;//pour corbeille
    QGridLayout *leftLayout = new QGridLayout;//pour corbeille
    //QGridLayout *leftdownLayout = new QGridLayout;//pour corbeille
    QGridLayout *rightLayout = new QGridLayout;//pour corbeille
    leftLayout->addWidget(listView,0,0,2,1);//pour corbeille
    leftLayout->addWidget(CorbeilleView,2,0,1,1);//pour corbeille
    rightLayout->addWidget(noteView);//pour corbeille
    mainLayout->addLayout(leftLayout,0,0);//pour corbeille
    mainLayout->addLayout(rightLayout,0,1);//pour corbeille
    setLayout(mainLayout);

    connect(listView, SIGNAL(noteSelected(const Note *)), noteView, SLOT(setNote(const Note*)));
    connect(noteView, SIGNAL(noteUpdated(const Note *)), &data, SLOT(updateNote(const Note *)));
    connect(CorbeilleView, SIGNAL(noteSelected(const Note *)), noteView, SLOT(setNoteArchive(const Note*)));//pour corbeille



}

Mainframe::Mainframe(NotesManager& nm,Corbeille& cb ,QWidget *parent): QWidget(parent), data(nm),cb(cb){
    initUI();
    show();
}
