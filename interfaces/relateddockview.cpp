#include "relateddockview.h"
#include <QDebug>

RelatedDockView::RelatedDockView(RelationsManager<Note>& relationsManager, QWidget *parent) : QWidget(parent), relationsManager(relationsManager)
{
    initUI();
    setSelectedNote(nullptr);
}

void RelatedDockView::initUI(){
    layout = new QVBoxLayout;

    linkButton = new QPushButton("Lier à...");
    linkButton->setAutoDefault(true);
    linkButton->setDefault(true);

    createDialog = new CreateLinkDialog(relationsManager ,this);

    connect(linkButton, SIGNAL(pressed()), createDialog, SLOT(open()));
    connect(createDialog, SIGNAL(accepted()), this, SLOT(refresh()));

    childrenView = new QTreeView;
    parentsView = new QTreeView;

    childrenView->setHeaderHidden(true);
    parentsView->setHeaderHidden(true);
    parentsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    childrenView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    childrenView->installEventFilter(this);
    parentsView->installEventFilter(this);

    childrenView->setModel(&childrenModel);
    parentsView->setModel(&parentsModel);

    layout->addWidget(linkButton);
    layout->addWidget(new QLabel("Descendants"));
    layout->addWidget(childrenView);
    layout->addWidget(new QLabel("Ascendants"));
    layout->addWidget(parentsView);

    deleteConfirm = new QMessageBox(this);
    deleteConfirm->setIcon(QMessageBox::Warning);
    deleteConfirm->setModal(true);
    deleteConfirm->setWindowModality(Qt::WindowModal);
    deleteConfirm->addButton("Supprimer", QMessageBox::DestructiveRole);
    deleteConfirm->addButton("Annuler", QMessageBox::RejectRole);
    deleteConfirm->setText("Souhaitez-vous supprimer cette relation ?");

    setMinimumSize(250, 0);
    setLayout(layout);
}


void RelatedDockView::setSelectedNote(const Note* n){
    selectedNote = n;

    if(n != nullptr){
        createDialog->setCurrentNote(*n);
    }

    refresh();

}

void RelatedDockView::refresh(){
    if(selectedNote == nullptr){
        childrenModel.clear();
        parentsModel.clear();
        linkButton->setDisabled(true);
    }else{
        linkButton->setDisabled(false);
        relationsManager.fillTree(&childrenModel, &childrenIndexMap, *selectedNote, RelationsManager<Note>::CHILD);
        relationsManager.fillTree(&parentsModel, &parentsIndexMap, *selectedNote, RelationsManager<Note>::PARENT);
        childrenView->expandToDepth(1);
        parentsView->expandToDepth(1);
    }
}

bool RelatedDockView::eventFilter(QObject *object, QEvent *event){
    if(event->type() == QEvent::KeyPress && (object == parentsView || object == childrenView)){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Delete || keyEvent->key() == Qt::Key_Backspace){
            bool parents = (object == parentsView);

            QModelIndex idx = (parents ? parentsView->currentIndex() : childrenView->currentIndex());
            const Association<Note>* assoc = (parents ? parentsIndexMap.value(idx) : childrenIndexMap.value(idx));
            if(assoc){

                deleteConfirm->setInformativeText("Relation entre " + assoc->getRelatedFrom() + " et " + assoc->getRelatedTo() + " de type " + assoc->getRelation().getName());
                int code = deleteConfirm->exec();
                if(code == 0){
                    relationsManager.unlink(assoc->getRelation(), assoc->getRelatedFrom(), assoc->getRelatedTo());
                    refresh();
                }
            }
        }
    }
    return NULL;
}


