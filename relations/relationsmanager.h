#ifndef RELATIONSMANAGER_H
#define RELATIONSMANAGER_H

#include <stdio.h>
#include <QString>
#include <QVector>
#include "relationship.h"
#include "bidirectionalrelationship.h"
#include "utils.h"

//template <typename> class Relationship;

template<typename T>
class RelationsManager
{

    QVector<Relationship<T>*> relationships;

public:
    /* Crée un nouveau gestionnaire de relations */
    RelationsManager() : relationships(0){}

    /* Crée une nouvelle relation bidirectionelle ou non.
     * Lance AppException une relation du même nom existe*/
    Relationship<T>& createRelation(const QString& title, bool bidirectional = false);

    /* Retourne une relation par son nom*/
    Relationship<T>& getRelation(const QString& title);

    /* Lie deux objets entre eux par la relation et la label correspondant.
     * L'ordre est important, sauf pour les relations bidirectionelles
     * Si les objets sont déjà liés par cette relation, met simplement à jour le label. */
    void link(Relationship<T>& relation, const T& ref1, const T& ref2, const QString& label = "");

    /* Détermine si deux objets sont liés par une relation.
     * L'ordre compte, sauf pour les relations bidirectionelles */
    bool areLinked(Relationship<T>& relation, const T& ref1, const T& ref2) const;

    /* Retire une relation entre deux objets.
     * L'ordre compte, sauf pour les relations bidirectionelles
     * Si les deux objets n'étaient pas liés, ne fait rien */
    void unlink(Relationship<T>& relation, const T& ref1, const T& ref2);
};

template<typename T>
Relationship<T>& RelationsManager<T>::createRelation(const QString& title, bool bidirectional){

    // On vérifie si la relation n'existe pas déjà
    Relationship<T>* const * i;
    for(i = relationships.constBegin(); i != relationships.constEnd(); ++i){
        if((*i)->title == title){
            throw new AppException("La relation existe déjà");
        }
    }

    // Création de la relation
    Relationship<T>* r;
    if(bidirectional){
        r = new BidirectionalRelationship<T>(title);
    }else{
        r = new Relationship<T>(title);
    }

    relationships.append(r);
    return *r;

}

template<typename T>
Relationship<T>& RelationsManager<T>::getRelation(const QString& title) {
    Relationship<T>** i;
    for(i = relationships.begin(); i != relationships.end(); ++i){
        if((*i)->title == title){
            return *i;
        }
    }
}

template<typename T>
void RelationsManager<T>::link(Relationship<T>& relation, const T& ref1, const T& ref2, const QString& label){
    relation.associate(ref1, ref2, label);
}

template<typename T>
bool RelationsManager<T>::areLinked(Relationship<T> &relation, const T& ref1, const T& ref2) const{
    return relation.areAssociated(ref1, ref2);
}

template<typename T>
void RelationsManager<T>::unlink(Relationship<T> &relation, const T& ref1, const T& ref2){
    relation.dissociate(ref1, ref2);
}


#endif // RELATIONSMANAGER_H
