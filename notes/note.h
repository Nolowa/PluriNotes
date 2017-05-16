#ifndef NOTE_H
#define NOTE_H

#include <QUuid>
#include <QString>
#include <QDateTime>
#include <QWidget>
#include "utils.h"
#include <QStandardItem>

typedef enum {active, non_editable,sursis} State;// active=0, non_editable=1, sursis=2

class Note : public QStandardItem{
    QUuid identifier;
    QString title;
    QDateTime created;
    QDateTime edited;
    State state;

    static const QString type;

public:
    Note(QUuid identifier);
    //Note(const Note& n); // celui de base is suffisant
    const QUuid getIdentifier() const;
    const QString& getTitle() const;
    const QDateTime getCreated() const;
    const QDateTime getEdited() const;
    const QString getState() const;
    State getStates() const;

    void setTitle(const QString& t);
    void setState(State s);
    void setCreated(QDateTime c); //sert à restore
    void setEdited(QDateTime e); //sert à restore

    bool operator==(const Note &other) const{ return identifier == other.identifier;}

    // a voir si on peut la mettre en privée
    void setEdited(); // a mettre dans la méthode dès que l'on change une valeur d'attribut (sauf pour l'état de la note)

    void load(const Note& n);
    //Note* save();

    virtual ~Note();

    virtual const QString& getType() const;

    //virtual QStandardItem *clone() const;
};

#endif // NOTE_H
