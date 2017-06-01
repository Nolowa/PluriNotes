#ifndef RELATIONSMANAGER_H
#define RELATIONSMANAGER_H

#include <QObject>
#include <QDebug>
#include <stdio.h>
#include <QString>
#include <QVector>
#include <QMap>
#include <QStack>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMultiMap>
#include <QStringList>
#include "relationship.h"
#include "bidirectionalrelationship.h"
#include "utils.h"

template<typename T>
class RelationsManager
{

    QVector<Relationship<T>*> relationships;

    void fillTreeInternal(const T* root, QStack<const Association<T>*>* els_stack, QStandardItem* el_item, QMap<QModelIndex,  const Association<T>*>* indexMap, int dir) const;

public:

    enum Direction {PARENT, CHILD};

    /* Crée un nouveau gestionnaire de relations */
    RelationsManager() : relationships(0){}

    /* Crée une nouvelle relation bidirectionelle ou non.
     * Lance AppException une relation du même nom existe*/
    Relationship<T>& createRelation(const QString& title, bool bidirectional = false);

    /* Retourne une relation par son nom*/
    Relationship<T>& getRelation(const QString& title);

    /* Retourne la liste des relations disponibles */
    QStringList getRelationsName() const;

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

    QVector<const Association<T>*>* getChildren(const T& ref) const;

    QVector<const Association<T>*>* getParents(const T& ref) const;

    void fillTree(QStandardItemModel* model, QMap<QModelIndex, const Association<T>*>* indexMap, const T& ref, int dir) const;

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

    relationships.push_back(r);

    return *r;

}

template<typename T>
Relationship<T>& RelationsManager<T>::getRelation(const QString& title) {
    Relationship<T>** i;
    for(i = relationships.begin(); i != relationships.end(); ++i){
        if((*i)->title == title){
            return **i;
        }
    }

    throw new AppException("Relation inexistante");
}

template<typename T>
QStringList RelationsManager<T>::getRelationsName() const {
    QStringList l;
    Relationship<T>* const * i;
    for(i = relationships.constBegin(); i != relationships.constEnd(); ++i){
        l << (*i)->getName();
    }
    return l;
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


template<typename T>
void RelationsManager<T>::fillTree(QStandardItemModel* model, QMap<QModelIndex, const Association<T>*>* indexMap, const T& ref, int dir) const{
    model->clear();
    indexMap->clear();

    // Pile permettant de mémoriser les éléments déjà visités dans une branche de l'arbre
    // Cela permet d'éviter de générer un artbre infini si on a ce genre de relation par exemple :
    // A -> B -> C -> A (-> B -> C -> A -> B -> C -> etc...)
    QStack<const Association<T>*>* elements_stack = new QStack<const Association<T>*>;
    //elements_stack->push(&ref);
    fillTreeInternal(&ref, elements_stack, model->invisibleRootItem(), indexMap, dir);

    delete elements_stack;

}



template<typename T>
void RelationsManager<T>::fillTreeInternal(const T* root, QStack<const Association<T>*>* els_stack, QStandardItem* el_item, QMap<QModelIndex,  const Association<T>*>* indexMap, int dir) const{

    bool placingRoot;
    QStandardItem* newItem;
    const Association<T>* currentAssoc = 0;
    const T* currentEl;

    if(els_stack->empty()){
        placingRoot = true;
        currentEl = root;

        newItem = new QStandardItem(*currentEl);

    }else{
        placingRoot = false;

        currentAssoc = els_stack->pop();
        currentEl = (dir == PARENT  ? &currentAssoc->getRelatedFrom() : &currentAssoc->getRelatedTo());
        QString str = *currentEl + " #" + currentAssoc->getRelation().getName() + " (" + currentAssoc->getLabel() + ")";
        newItem = new QStandardItem(str);

    }

    el_item->appendRow(newItem);

    if(!placingRoot){
        indexMap->insert(newItem->index(), currentAssoc);
    }

    if(placingRoot || !els_stack->contains(currentAssoc)){

        if(!placingRoot) els_stack->push(currentAssoc);

        QVector<const Association<T>*>* map = (dir == PARENT ? getParents(*currentEl) : getChildren(*currentEl));
        for(typename QVector<const Association<T>*>::const_iterator it = map->constBegin(); it != map->constEnd(); it++){

                els_stack->push_back(*it);
                //els_stack->push();
                fillTreeInternal(root, els_stack, newItem, indexMap, dir);

        }

        if(!placingRoot) els_stack->pop();


        delete map;
    }
}



template<typename T>
QVector<const Association<T>*>* RelationsManager<T>::getChildren(const T& ref) const{

    QVector<const Association<T>*>* results = new QVector<const Association<T>*>();
    //QMultiMap<const T*, const Relationship<T>*>* multimap = new QMultiMap<const T*, const Relationship<T>*>;

    for(const Relationship<T>* const * r = relationships.constBegin(); r < relationships.constEnd(); r++){
        QVector<const Association<T>*>* relChildren = (*r)->getChildren(ref);
        for(const Association<T>* const * t = relChildren->constBegin(); t < relChildren->constEnd(); t++){
            //multimap->insert(*t, *r);
            results->push_back(*t);
        }

        delete relChildren;
    }

    return results;
}

template<typename T>
QVector<const Association<T>*>* RelationsManager<T>::getParents(const T& ref) const{

    QVector<const Association<T>*>* results = new QVector<const Association<T>*>();
    //QMultiMap<const T*, const Relationship<T>*>* multimap = new QMultiMap<const T*, const Relationship<T>*>;

    for(const Relationship<T>* const * r = relationships.constBegin(); r < relationships.constEnd(); r++){
        QVector<const Association<T>*>* relParents = (*r)->getParents(ref);
        for(const Association<T>* const * t = relParents->constBegin(); t < relParents->constEnd(); t++){
            //multimap->insert(*t, *r);
            results->push_back(*t);
        }

        delete relParents;
    }

    return results;
}



#endif // RELATIONSMANAGER_H
