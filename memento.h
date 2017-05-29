#ifndef MEMENTO_H
#define MEMENTO_H
#include "notes/note.h"
#include<vector>


class Memento{
    Note* note;
public:
    Memento(){}
    virtual Note* getState() const{return note;}

};

class MementoNote: public Memento{
    Note* m_note;
public:
    MementoNote& operator=(const MementoNote &memento){m_note = memento.m_note; return *this;}
    Note* getState()const {return m_note;}
};


// A voir ce que nous devons enregister pour les relations
class MementoRelation: public Memento{
    //Note* m_note;
public:
    MementoRelation& operator=(const MementoRelation &memento);
    //Note* getState()const {return m_note;}
};


class MementoCorbeille: public Memento{
    Note* m_note;
public:
    MementoCorbeille& operator=(const MementoCorbeille &memento){m_note = memento.m_note; return *this;}
    Note* getState()const {return m_note;}
};




class MementoCaretaker: public QWidget {
   Q_OBJECT
   std::vector<Memento> m_vecMemento; // pour le controle Z: annuler
   std::vector<Memento> m_vecMementoInverse; // pour le controle Y: rétablir

public:
    MementoCaretaker(){}


public slots:
    void undo();
    void redo();
    void save(const Memento& memento);

signals:
    void DeleteOnNotesListView(const Note*);
    void CreateOnNotesListView(const Note*);
    //void DeleteRelation(const QUELQUECHOSE);
    //void CreateRelation(const QUELQUECHOSE);
    void DeleteOnCorbeille(const Note*);
    void PutOnCorbeille(const Note*);



};

#endif // MEMENTO_H
