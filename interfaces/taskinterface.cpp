#include "taskinterface.h"

TaskInterface::TaskInterface(const Task& t,QWidget *parent): GeneralInterface(parent),task(&t){
    layout=new QFormLayout;

    generate= new QPushButton(QString("Enregistrer"));
    titleEdit= new QLineEdit(task->getTitle(),this);
    actionEdit= new QTextEdit(task->getActionToBeDone(),this);
    //QString date=QDateTime::currentDateTime().toString();
    dateEdit= new QLineEdit(task->getExpired().toString(),this);
    idEdit= new QLineEdit(task->getIdentifier().toString(),this);
    idEdit->setReadOnly(1);
    idEdit->setFixedWidth(300);
    statusCombo= new QComboBox(this);
    priorityCombo= new QComboBox(this);

    // priority
    priorityCombo->addItem("0");
    priorityCombo->addItem("1");
    priorityCombo->addItem("2");
    priorityCombo->addItem("3");
    priorityCombo->addItem("4");
    priorityCombo->addItem("5");
    priorityCombo->setCurrentIndex(task->getPriority());

    // status
    statusCombo->addItem("En attente");
    statusCombo->addItem("En cours");
    statusCombo->addItem("Terminée");
    statusCombo->setCurrentIndex(task->getStatusInt());

    //Fixation des tailles des Widgets
    dateEdit->setFixedWidth(180);
    titleEdit->setFixedWidth(180);
    //ajout des Widget sur le layout
    layout->addRow("Identifiant :",idEdit);
    layout->addRow("Titre :",titleEdit);
    layout->addRow("Status :",statusCombo);
    layout->addRow("Priorité :",priorityCombo);
    layout->addRow("Date échouant",dateEdit);
    layout->addRow("Objectif :",actionEdit);
    layout->addWidget(generate);

    setLayout(layout);
    setWindowTitle("Tâche à réaliser");

    //slot
    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(save()));


}

//slots
void TaskInterface::save(){
    Task* t = new Task(*task);
    t->setTitle(titleEdit->text());
    t->setStatus(Status(statusCombo->currentIndex()));
    t->setPriority(priorityCombo->currentIndex());
    t->setActionToBeDone(actionEdit->toPlainText());
    t->setExpired(QDateTime::fromString(dateEdit->text()));

    task = t;
    emit newVersion(t); // signal d'émition pour la création d'une nouvelle version
    //QMessageBox::information(this, "Fichier", "Enregisterment de :\n" +titleEdit->text() +"\n"+statusCombo->currentText() + "\n" +priorityCombo->currentText() + "\n" +actionEdit->toPlainText() + "\n" +dateEdit->text()+ "\n"+ QDateTime::fromString(dateEdit->text()).toString());

}
