#include "noteslistview.h"
#include "utils.h"
#include <QVBoxLayout>
#include <QFrame>
#include "notes/note.h"
#include <QUuid>
#include "iostream"

NotesListView::NotesListView(NotesManager& nm, QWidget *parent) : QWidget(parent), nm(nm)
{
    generateModel();
    initUI();

    QObject::connect(&nm, SIGNAL(noteCreated(Note)), this, SLOT(noteAdded(Note)));
    QObject::connect(&nm, SIGNAL(noteUpdated(Note)), this, SLOT(noteUpdated(Note)));
    connect(listview->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChanged(QItemSelection, QItemSelection)));
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
    listview->clearSelection();
    // Barre "nouveau"
    btnsLayout = new QHBoxLayout(this);
    buttons = new QPushButton*[5];

    buttons[0] = new QPushButton(QIcon(":/icons/article"),"");
    buttons[1] = new QPushButton(QIcon(":/icons/task"),"");
    buttons[2] = new QPushButton(QIcon(":/icons/image"),"");
    buttons[3] = new QPushButton(QIcon(":/icons/sound"),"");
    buttons[4] = new QPushButton(QIcon(":/icons/video"),"");

    QObject::connect(buttons[0], SIGNAL(pressed()), &nm, SLOT(createArticle()));
    QObject::connect(buttons[1], SIGNAL(pressed()), &nm, SLOT(createTask()));
    QObject::connect(buttons[2], SIGNAL(pressed()), &nm, SLOT(createImage()));
    QObject::connect(buttons[3], SIGNAL(pressed()), &nm, SLOT(createSound()));
    QObject::connect(buttons[4], SIGNAL(pressed()), &nm, SLOT(createVideo()));

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
    layout->setMargin(0);
    this->setLayout(layout);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(41, 128, 185));
    setAutoFillBackground(true);
    setPalette(pal);

    setMaximumWidth(300);


}

QStandardItem* NotesListView::generateItem(const Note& note){
    // TODO: Modifier l'icone en fonction du type de note

    QString qstr = QString(":/icons/") + note.getType().toLower();

    QStandardItem* item = new QStandardItem(QIcon(qstr), note.getTitle().length() ? note.getTitle() : "Note sans nom");
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

void NotesListView::selectionChanged(QItemSelection cur, QItemSelection prev){
    if(cur.size()){
        const QUuid& uuid = indexMap.key(cur.indexes().first());
        const Note* note = nm.find(uuid);
        emit noteSelected(note);
    }else{
        emit noteSelected(nullptr);
    }
}
