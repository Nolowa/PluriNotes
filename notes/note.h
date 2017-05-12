#ifndef NOTE_H
#define NOTE_H

#include <QUuid>
#include <QString>
#include <QDateTime>
#include <QWidget>
#include "utils.h"

typedef enum {active, non_editable,sursis} State;// active=0, non_editable=1, sursis=2

class Note {
    QUuid identifier;
    QString title;
    QDateTime created;
    QDateTime edited;
    State state;


public:
    Note(QUuid identifier);
    const QUuid getIdentifier() const;
    const QString& getTitle() const;
    const QDateTime getCreated() const;
    const QDateTime getEdited() const;
    const QString getState() const;
    const State getStates() const;

    void setTitle(const QString& t);
    void setState(State s);
    void setCreated(QDateTime c);//sert à restore
    void setEdited(QDateTime e);//sert à restore
    void setIdentifier(QUuid i);//sert à restore

    // a voir si on peut la mettre en privée
    void setEdited(); // a mettre dans la méthode dès que l'on change une valeur d'attribut (sauf pour l'état de la note)

    Note(const Note& n);
    void restore(const Note& n);
    Note* save();

    virtual ~Note();
};

#endif // NOTE_H
