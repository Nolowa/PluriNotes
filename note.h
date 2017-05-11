#ifndef NOTE_H
#define NOTE_H

#include <QUuid>
#include <QString>
#include <QDateTime>

class Note{
    QUuid identifier;
    QString title;
    enum state {active, non_editable,sursis};
    QDateTime created;
    QDateTime edited;
    enum genre {article,image,sound,task,video};//favorable à memento

    // méthode privée
    void setEdited(); // a mettre dans la méthode dès que l'on change une valeur d'attribut

public:
    Note(QUuid identifier);
    const QUuid getIdentifier() const;
    const QString getTitle() const;
    const QDateTime getCreated() const;
    const QDateTime getEdited() const;
    void setTitle(const QString& t);




    //~Note();
};

#endif // NOTE_H
