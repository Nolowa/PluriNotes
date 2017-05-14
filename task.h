#ifndef TASK_H
#define TASK_H


#include "note.h"
#include "taskinterface.h"

class TaskInterface;

typedef enum {en_attente, en_cours,terminee} Status;// en_attente=0, en_cours=1, terminee=2

class Task: public Note {
    QString actionToBeDone;
    Status status; // enumeration
    unsigned int priority; //{0,1,2,3,4,5}  0:pas de priorité; 5: très élevé :facultatif
    QDateTime expired; // facultatif, date échouante

public:
    Task(QUuid identifier);

    const QString& getActionToBeDone() const;
    QString getStatus() const;
    unsigned int getStatusInt() const;
    unsigned int getPriority() const;
    const QDateTime& getExpired() const;

    void setActionToBeDone(const QString& a);
    void setPriority(unsigned int p);
    void setStatus(Status s);
    void setExpired(const QDateTime exp);
    TaskInterface* getInterface();


};

#endif // TASK_H
