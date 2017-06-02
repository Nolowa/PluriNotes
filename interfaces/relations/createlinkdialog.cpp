#include "createlinkdialog.h"
#include <QDebug>

CreateLinkDialog::CreateLinkDialog(RelationsManager<NoteHolder>& relationsManager ,QWidget *parent) : QDialog(parent, Qt::Sheet), relationsManager(relationsManager)
{
    initUI();
    populate();

}


void CreateLinkDialog::initUI(){
    glblLayout = new QVBoxLayout;
    formLayout = new QFormLayout;
    relatedCombo = new QComboBox;
    relationCombo = new QComboBox;
    labelField = new QLineEdit;
    btnsLayout = new QDialogButtonBox;

    QPushButton* linkBtn = btnsLayout->addButton("Lier", QDialogButtonBox::AcceptRole);
    QPushButton* cancelBtn = btnsLayout->addButton("Annuler", QDialogButtonBox::RejectRole);


    formLayout->addRow("Relation :", relationCombo);
    formLayout->addRow("Destination :", relatedCombo);
    formLayout->addRow("Label :", labelField);


    glblLayout->addWidget(new QLabel("Spécifiez les caractéristiques du lien à créer pour cette note."));
    glblLayout->addLayout(formLayout);
    glblLayout->addWidget(btnsLayout);

    connect(linkBtn, SIGNAL(pressed()), this, SLOT(accept()));
    connect(cancelBtn, SIGNAL(pressed()), this, SLOT(reject()));

    setLayout(glblLayout);
    setModal(true);
}

void CreateLinkDialog::populate(){

    QStringList l = relationsManager.getRelationsName();
    relatedCombo->setModel(&notesManager.getModelHolder().getModel());
    relationCombo->clear();
    relationCombo->addItems(l);
}

void CreateLinkDialog::setCurrentNote(const NoteHolder &n){
    currentNote = &n;
}

void CreateLinkDialog::accept(){

        Relationship<NoteHolder>& rel = relationsManager.getRelation(relationCombo->currentText());
        int idx = relatedCombo->currentIndex();
        QModelIndex qidx = relatedCombo->model()->index(idx, 0);
        const NoteHolder& nh = notesManager.getModelHolder().findByIndex(qidx);

        if(relationsManager.areLinked(rel, *currentNote, nh)){
            QMessageBox::warning(this, "Liaison impossible",
                                           "Les notes sélectionnés sont déjà liés par cette relation.",
                                           QMessageBox::Ok,
                                           QMessageBox::Ok);
        }else{
            relationsManager.link(rel, *currentNote, nh, labelField->text());
            QDialog::accept();

            emit linkCreated(rel.getName(), *currentNote, nh, labelField->text());
        }



}
