#include "memento.h"
#include <QMessageBox>
//
// MementoCaretaker
//

void MementoCaretaker::undo() {
    if(m_vecMemento.size()!=0){
        Memento* mem=m_vecMemento.back();
        m_vecMemento.pop_back();
        m_vecMementoInverse.push_back(mem);
        if (typeid(*mem)==typeid(MementoNoteState)){emit changeNoteState(mem->getNote(), mem->getOldState());}
        else
            if (typeid(*mem)==typeid(MementoRelation)){emit DeleteRelation(mem->getNameLabel(),mem->getNote(),mem->getNote1(),mem->getNameRelation());}
            else throw("Error de TypeMemento");

    }
    else{
        std::cout<<"rien à annuler"<<std::endl;
    }
     std::cout<<"UNDO"<<std::endl;
}



void MementoCaretaker::save(Memento* memento) {
    m_vecMemento.push_back(memento);
}

void MementoCaretaker::redo(){
    if (m_vecMementoInverse.size()!=0){
        Memento* mem= m_vecMementoInverse.back();
        m_vecMementoInverse.pop_back();
        m_vecMemento.push_back(mem);
        if (typeid(*mem)==typeid(MementoNoteState)){emit changeNoteState(mem->getNote(), mem->getNewState());}
        else
            if (typeid(*mem)==typeid(MementoRelation)){emit CreateRelation(mem->getNameLabel(),mem->getNote(),mem->getNote1(),mem->getNameRelation());}
            else throw("Error de TypeMemento");
    }
    else{
        std::cout<<"rien à rétablir"<<std::endl;
    }
    std::cout<<"REDO"<<std::endl;
    //QMessageBox::information(this,QString("great!"),QString("great"));

}
