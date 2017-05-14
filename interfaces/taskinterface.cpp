#include "taskinterface.h"

TaskInterface::TaskInterface(Task* t,QWidget *parent): QWidget(parent),task(t){
    layout=new QFormLayout;

    generate= new QPushButton(QString("Enregistrer"));
    titleEdit= new QLineEdit(task->getTitle(),this);
    actionEdit= new QTextEdit(task->getActionToBeDone(),this);
    //QString date=QDateTime::currentDateTime().toString();
    dateEdit= new QLineEdit(task->getExpired().toString(),this);
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
    task->setTitle(titleEdit->text());
    task->setStatus(Status(statusCombo->currentIndex()));
    task->setPriority(priorityCombo->currentIndex());
    task->setActionToBeDone(actionEdit->toPlainText());
    task->setExpired(QDateTime::fromString(dateEdit->text()));
    //QMessageBox::information(this, "Fichier", "Enregisterment de :\n" +titleEdit->text() +"\n"+statusCombo->currentText() + "\n" +priorityCombo->currentText() + "\n" +actionEdit->toPlainText() + "\n" +dateEdit->text()+ "\n"+ QDateTime::fromString(dateEdit->text()).toString());

}
