#ifndef MEMENTO_H
#define MEMENTO_H
#include "notes/note.h"
#include<vector>
class Memento{
    Note* m_note;
public:
    Memento(Note* n){ m_note = new Note(n); }
    Memento();
    Memento& operator=(const Memento &memento)
    {
        m_note = memento.m_note;
        return *this;
    }
    Note* getM_note()const {return m_note;}
};

class MementoCaretaker {
   std::vector<Memento> m_vecMemento;

public:
    MementoCaretaker(){}
    Memento Load(int state) {
        return m_vecMemento[state];;
    }

    void Save(Memento memento) {
        m_vecMemento.push_back(memento);
    }
};

#endif // MEMENTO_H
