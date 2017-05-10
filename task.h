#ifndef TASK_H
#define TASK_H


#include "note.h"


class Task: public Note {
    QString actionToBeDone;
    enum status {en_attente,en_cours,terminee};
    unsigned int priority; //{0,1,2,3,4,5}
    QDateTime echouant;
public:
    Task(QUuid identifier);
};

#endif // TASK_H
