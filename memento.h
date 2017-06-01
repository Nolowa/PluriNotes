#ifndef MEMENTO_H
#define MEMENTO_H
#include "notes/note.h"
#include "relations/association.h"
#include<vector>
#include <QString>

template <typename> class Association;

class Memento{
    Note* notes;
    Association<Note>* relation;
public:
    Memento(){}
    virtual Note* getState() const{return notes;}
    virtual Association<Note>* getRelation()const{return relation;}

};

class MementoNote: public Memento{
    Note* m_note;
public:
    MementoNote(Note* note): m_note(note){}
    MementoNote& operator=(const MementoNote &memento){m_note = memento.m_note; return *this;}
    Note* getState()const {return m_note;}
};


// A voir ce que nous devons enregister pour les relations
class MementoRelation: public Memento{
    Association<Note>* m_relation;
public:
    MementoRelation( Association<Note>* a):m_relation(a){}
    MementoRelation& operator=(const MementoRelation &memento);
    Association<Note>* getRelation()const {return m_relation;}
};


class MementoCorbeille: public Memento{
    Note* m_note;
public:
    MementoCorbeille(Note* note): m_note(note){}
    MementoCorbeille& operator=(const MementoCorbeille &memento){m_note = memento.m_note; return *this;}
    Note* getState()const {return m_note;}
};




class MementoCaretaker: public QObject{
   Q_OBJECT
   std::vector<Memento> m_vecMemento; // pour le controle Z: annuler
   std::vector<Memento> m_vecMementoInverse; // pour le controle Y: rétablir
   void save(const Memento& memento);
public:
    MementoCaretaker(){}


public slots:
    void undo();
    void redo();

    void saveMementoRelation( Association<Note>* a) { save(MementoRelation(a)); std::cout<<"Enregistrement ok relation memento";}
    void saveMementoListView( Note* n) {save(MementoNote(n)); std::cout<<"Enregistrement ok ListView memento";}
    void saveMementoCorbeille( Note* n){save(MementoCorbeille(n)); std::cout<<"Enregistrement ok corbeille memento";}



signals:
    void DeleteOnNotesListView(const Note*);
    void CreateOnNotesListView(const Note*);

    void DeleteRelation(const Association<Note>*);
    void CreateRelation(const Association<Note>*);

    void DeleteOnCorbeille(const Note*);
    void PutOnCorbeille(const Note*);

};

#endif // MEMENTO_H
