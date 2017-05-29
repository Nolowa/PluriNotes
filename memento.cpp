#include "memento.h"

//
// MementoCaretaker
//

void MementoCaretaker::undo() {
    if(m_vecMemento.size()!=0){
        Memento mem=m_vecMemento.back();
        m_vecMemento.pop_back();
        m_vecMementoInverse.push_back(mem);
        if (typeid(mem)==typeid(MementoNote)){emit DeleteOnNotesListView(mem.getState());}
        if (typeid(mem)==typeid(MementoCorbeille)){emit DeleteOnCorbeille(mem.getState());}
        //if (typeid(mem)==typeid(MementoRelation)){emit ;}
        throw("Error de TypeMemento");
    }
}

void MementoCaretaker::save(const Memento& memento) {
    m_vecMemento.push_back(memento);
}

void MementoCaretaker::redo(){
    if (m_vecMementoInverse.size()!=0){
        Memento mem= m_vecMementoInverse.back();
        m_vecMementoInverse.pop_back();
        m_vecMemento.push_back(mem);
        if (typeid(mem)==typeid(MementoNote)){emit CreateOnNotesListView(mem.getState());}
        if (typeid(mem)==typeid(MementoCorbeille)){emit PutOnCorbeille(mem.getState());}
        //if (typeid(mem)==typeid(MementoRelation)){emit ;}
        throw("Error de TypeMemento");
    }
}
