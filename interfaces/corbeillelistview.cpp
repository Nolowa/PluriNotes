#include "corbeillelistview.h"
#include "notes/note.h"
#include <QtDebug>
CorbeilleListView::CorbeilleListView(Corbeille& cob,QWidget* parent):QWidget(parent),cb(cob)
{
    generateModel();
    initUI();

    QObject::connect(&cb, SIGNAL(noteCreatedc(Note)), this, SLOT(noteAdded(Note)));
    //QObject::connect(&cb, SIGNAL(noteUpdated(Note)), this, SLOT(noteUpdated(Note)));
    connect(listview->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChanged(QItemSelection, QItemSelection)));

}


void CorbeilleListView::generateModel(){
   for (Corbeille::Iterator it = cb.getIterator(); !it.isDone(); it.next()) {
        const Note& n = it.current();

        // Ajout de la note au modèle
        generateItem(n);


    }
}

void CorbeilleListView::initUI(){

    layout = new QVBoxLayout(this);

    listview = new QListView(this);
    listview->setModel(&model);
    listview->setIconSize(QSize(16, 16));
    listview->setStyleSheet("background: #fcfcfc; border:0;");
    listview->clearSelection();
    // Barre "nouveau"
    btnsLayout = new QHBoxLayout(this);
    buttons = new QPushButton*[3];

    buttons[0] = new QPushButton(QIcon(":/icons/vide"),"");
    buttons[1] = new QPushButton(QIcon(":/icons/archive"),"");
    buttons[2] = new QPushButton(QIcon(":/icons/corbeille"),"");

    //QObject::connect(buttons[0], SIGNAL(pressed()), &cb, SLOT(createArticle()));
    //QObject::connect(buttons[1], SIGNAL(pressed()), &cb, SLOT(createTask()));
    QObject::connect(buttons[0], SIGNAL(pressed()), &cb, SLOT(vidage()));

    for(int i = 0; i < 3; i++){
        buttons[i]->setMaximumSize(35, 35);
        buttons[i]->setMinimumSize(35, 35);
        buttons[i]->setIconSize(QSize(21, 21));
        buttons[i]->setStyleSheet("QPushButton{background-color: #B9E2F0; border-style: outset; border-radius: 10.5px; } QPushButton:hover{ background-color:#A2D1E0; } QPushButton:pressed{ background-color:#88BFD1; }");
        btnsLayout->addWidget(buttons[i]);
    }

    QFrame* btnsFrame = new QFrame;
    btnsFrame->setLayout(btnsLayout);

    layout->addWidget(listview);
    layout->addWidget(btnsFrame);

    layout->setMargin(0);
    this->setLayout(layout);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(41, 128, 185));
    setAutoFillBackground(true);
    setPalette(pal);

    setMaximumWidth(300);


}

QStandardItem* CorbeilleListView::generateItem(const Note& note){

    QString qstr = QString(":/icons/") + note.getType().toLower();
    QStandardItem* item = new QStandardItem(QIcon(qstr), note.getTitle().length() ? note.getTitle() : "Note sans nom");
    qDebug()<<qstr;
    model.appendRow(item);
    indexMap.insert(QUuid(note.getIdentifier()), item->index());
    return item;
}

QStandardItem* CorbeilleListView::updateItem(QStandardItem* item, const Note& note){
    item->setText(note.getTitle().length() ? note.getTitle() : "Note sans nom");
    return item;
}


void CorbeilleListView::noteAdded(const Note& note){
    generateItem(note);
}

void CorbeilleListView::noteUpdated(const Note& note){
    const QModelIndex& index = indexMap.value(QUuid(note.getIdentifier()));
    QStandardItem* item = model.itemFromIndex(index);
    updateItem(item, note);
}

void CorbeilleListView::selectionChanged(QItemSelection cur, QItemSelection prev){
    if(cur.size()){
        const QUuid& uuid = indexMap.key(cur.indexes().first());
        const Note* note = cb.find(uuid);
        emit noteSelected(note);
    }else{
        emit noteSelected(nullptr);
    }
}
