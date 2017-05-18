#ifndef NOTE_H
#define NOTE_H

#include <QUuid>
#include <QString>
#include <QDateTime>
#include <QWidget>
#include "utils.h"
#include <QStandardItem>


typedef enum {active, non_editable,sursis} State;// active=0, non_editable=1, sursis=2
/*! Classe Note, classe mère  */
class Note : public QStandardItem{
    QUuid identifier; /**< identifiant unique qui caractérise chaque objet Note, unique pour chaque objet Note  */
    QString title; /**< titre de la Note  */
    QDateTime created; /**< date de création de la Note  */
    QDateTime edited; /**< date de dernière mise à jour de la Note  */
    State state; /**< Etat de la note {active, non_editable,sursis}  */
    mutable QString filename;
    static const QString type;

public:
    Note(QUuid identifier);  /**< Constructeur */
    Note(Note* n); // celui de base is suffisant
    const QUuid getIdentifier() const; /**< Accesseur de l'attribut identifier */
    const QString& getTitle() const; /**< Accesseur de l'attribut title */
    const QDateTime getCreated() const; /**< Accesseur de l'attribut created */
    const QDateTime getEdited() const; /**< Accesseur de l'attribut edited */
    const QString getState() const; /**< Accesseur de l'attribut state */
    State getStates() const; /**< Accesseur de l'attribut state */

    void setTitle(const QString& t); /**< Méthode modifiant l'attribut title */
    void setState(State s); /**< Méthode modifiant l'attribut state */
    //sert à restore
    Note(QUuid identifier,QDateTime c);
    void setCreated(QDateTime c);  /**< Méthode modifiant l'attribut created */
    void setEdited(QDateTime e); /**< Méthode modifiant l'attribut edited */

    virtual QWidget* getUI() const = 0;

    bool operator==(const Note &other) const{ return identifier == other.identifier;} /**< Opérateur d'égalité (basé sur l'identifiant de la Note) */

    // a voir si on peut la mettre en privée
    // a mettre dans la méthode dès que l'on change une valeur d'attribut (sauf pour l'état de la note)
    void setEdited(); /**< Méthode modifiant l'attribut edited */

    void load(const Note& n);
    //Note* save();

    QString getFilename() const;
    void setFilename(const QString& f);

    virtual ~Note();

    virtual const QString& getType() const;

    //virtual QStandardItem *clone() const;
};

#endif // NOTE_H
