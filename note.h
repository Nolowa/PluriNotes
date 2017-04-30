#ifndef NOTE_H
#define NOTE_H

#include <QUuid>
#include <QString>
#include <QDateTime>

class Note
{
    QUuid identifier;
    QString title;

    QDateTime created;
    QDateTime edited;

    Note();

public:
    Note(QUuid identifier) : identifier(identifier){};
    const QUuid getIdentifier() const;
    const QString getTitle() const;
    const QDateTime getCreated() const;
    const QDateTime getEdited() const;


    //~Note();
};

#endif // NOTE_H
