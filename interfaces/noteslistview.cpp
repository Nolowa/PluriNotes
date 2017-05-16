#include "noteslistview.h"
#include "utils.h"
#include <QVBoxLayout>
#include <QFrame>

NotesListView::NotesListView(NotesManager& nm, QWidget *parent) : QWidget(parent), nm(nm)
{
    generateModel();
    initUI();

    QObject::connect(&nm, SIGNAL(noteCreated(Note)), this, SLOT(noteAdded(Note)));
    QObject::connect(&nm, SIGNAL(noteUpdated(Note)), this, SLOT(noteUpdated(Note)));
}

void NotesListView::generateModel(){
    Iterator<Note>& notes = nm.getIterator();
    while(!notes.isDone()){
        notes.next();
        Note& n = notes.current();

        // Ajout de la note au modèle
        generateItem(n);

    }
}

void NotesListView::initUI(){

    layout = new QVBoxLayout(this);

    listview = new QListView(this);
    listview->setModel(&model);
    listview->setIconSize(QSize(32, 32));
    listview->setStyleSheet("background: #fcfcfc; border:0;");
    // Barre "nouveau"
    btnsLayout = new QHBoxLayout(this);
    buttons = new QPushButton*[5];
    buttons[0] = new QPushButton(QIcon(":/icons/article"),"");
    buttons[1] = new QPushButton(QIcon(":/icons/task"),"");
    buttons[2] = new QPushButton(QIcon(":/icons/picture"),"");
    buttons[3] = new QPushButton(QIcon(":/icons/sound"),"");
    buttons[4] = new QPushButton(QIcon(":/icons/video"),"");

    for(int i = 0; i < 5; i++){
        buttons[i]->setMaximumSize(50, 50);
        buttons[i]->setMinimumSize(50,50);
        buttons[i]->setIconSize(QSize(30, 30));
        buttons[i]->setStyleSheet("QPushButton{background-color: #B9E2F0; border-style: outset; border-radius: 15px; } QPushButton:hover{ background-color:#A2D1E0; } QPushButton:pressed{ background-color:#88BFD1; }");
        btnsLayout->addWidget(buttons[i]);
    }

    QFrame* btnsFrame = new QFrame;
    btnsFrame->setLayout(btnsLayout);

    layout->addWidget(btnsFrame);
    layout->addWidget(listview);
    this->setLayout(layout);
    this->setStyleSheet("background: #2980b9;");




}

QStandardItem* NotesListView::generateItem(const Note& note){
    // TODO: Modifier l'icone en fonction du type de note
    QStandardItem* item = new QStandardItem(style()->standardIcon(QStyle::SP_FileIcon), note.getTitle().length() ? note.getTitle() : "Note sans nom");
    //indexMap.insert()
    model.appendRow(item);
    indexMap.insert(QUuid(note.getIdentifier()), item->index());
    return item;
}

QStandardItem* NotesListView::updateItem(QStandardItem* item, const Note& note){
    item->setText(note.getTitle().length() ? note.getTitle() : "Note sans nom");
    return item;
}


void NotesListView::noteAdded(const Note& note){
    generateItem(note);
}

void NotesListView::noteUpdated(const Note& note){
    const QModelIndex& index = indexMap.value(QUuid(note.getIdentifier()));
    QStandardItem* item = model.itemFromIndex(index);
    updateItem(item, note);
}
