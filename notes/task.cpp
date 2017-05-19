#include "task.h"

const QString Task::type = QString("Tâche");

// constructeur
Task::Task(QUuid identifier):Note(identifier),status(en_attente),priority(0){}

Task::Task(QUuid identifier, QDateTime c):Note(identifier,c),status(en_attente),priority(0){}

// accesseurs
 QString Task::getStatus() const{ //{en_attente, en_cours,terminee}
    if(status==0)
        return QString("en_attente");
    else if(status==1)
        return QString("en_cours");
    else
        return QString("terminee");
}

unsigned int Task::getPriority() const{
    return priority;
}

const QString& Task::getActionToBeDone() const{
    return actionToBeDone;
}

const QDateTime& Task::getExpired() const{
    return expired;
}

unsigned int Task::getStatusInt() const{
    return status;
}


// setters

void Task::setActionToBeDone(const QString& a){
    actionToBeDone=a;
    setEdited();
}

void Task::setPriority(unsigned int p){
    if (p>5)
        throw AppException("Error with priority level (must be beetween 0 and 5)");
    priority=p;
    setEdited();
}

void Task::setStatus(Status s){
    status=s;
    setEdited();
}

void Task::setExpired(const QDateTime exp){
    expired=exp;
    setEdited();
}

//Interface
QWidget* Task::getUI() const{
    return new TaskInterface(*this);
}

Status Task::getStatus_re() const{
    return status;
}

Note* Task::save(){
    Note* n=new Task(*this);
    return n;
}


void Task::restore(Note* n){
    Task* nouveau;
    nouveau=static_cast<Task*>(n);
    this->setTitle(nouveau->getTitle());
    this->setCreated(nouveau->getCreated());
    this->setState(nouveau->getStates());
    actionToBeDone=nouveau->getActionToBeDone();
    status=nouveau->getStatus_re();
    priority=nouveau->getPriority();
    expired=nouveau->getExpired();
}

const QString& Task::getType() const{
    return type;
}

