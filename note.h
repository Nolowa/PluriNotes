#ifndef NOTE_H
#define NOTE_H

#include <QUuid>
#include <QString>
#include <QDateTime>
#include "utils.h"

typedef enum {active, non_editable,sursis} State;// active=0, non_editable=1, sursis=2

class Note{
    QUuid identifier;
    QString title;
    QDateTime created;
    QDateTime edited;
<<<<<<< HEAD
    enum genre {article,image,sound,task,video};//favorable à memento
=======
    State state;
>>>>>>> 2f9f21b47e70ca72c232bc96d8d099876066e253


public:
    Note(QUuid identifier);
    const QUuid getIdentifier() const;
    const QString& getTitle() const;
    const QDateTime getCreated() const;
    const QDateTime getEdited() const;
    const QString getState() const;

    void setTitle(const QString& t);
    void setState(State s);

    // a voir si on peut la mettre en privée
    void setEdited(); // a mettre dans la méthode dès que l'on change une valeur d'attribut (sauf pour l'état de la note)


    virtual ~Note();
};

#endif // NOTE_H
