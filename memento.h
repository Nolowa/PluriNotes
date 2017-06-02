#ifndef MEMENTO_H
#define MEMENTO_H
#include "notes/note.h"
#include "relations/association.h"
#include "notes/noteholder.h"
#include <vector>
#include <QString>


class Memento{
public:
    Memento(){}
    virtual const NoteHolder& getNote() const=0;
    virtual const QString& getNameRelation()const=0;
    virtual const QString& getNameLabel() const=0;
    virtual const NoteHolder& getNote1() const=0;

    virtual const NoteState& getOldState()const=0;
    virtual const NoteState& getNewState()const=0;

};




class MementoRelation: public Memento{
    QString nameLabel;
    QString nameRelation;
    NoteHolder note;
    NoteHolder note1;

    //a supprimer
    NoteState oldState;
    NoteState newState;
public:
    MementoRelation(const QString& nameR,const NoteHolder& n, const NoteHolder& n1,const QString& nameL):nameLabel(nameL),nameRelation(nameR),note(n),note1(n1){}
    const QString& getNameRelation()const {return nameRelation;}
    const QString& getNameLabel() const {return nameLabel;}
    const NoteHolder& getNote1() const{return note1;}
    const NoteHolder& getNote() const {return note;}

    //a supprimer
    const NoteState& getOldState()const {return oldState;}
    const NoteState& getNewState()const {return newState;}

};



class MementoNoteState: public Memento{
    NoteHolder note;
    NoteState oldState;
    NoteState newState;

    //a supprimer
    QString nameLabel;
    QString nameRelation;
    NoteHolder note1;

public:
    MementoNoteState(const NoteHolder& n,NoteState oldS, NoteState newS): note(n),oldState(oldS),newState(newS){}
    const NoteHolder& getNote()const {return note;}
    const NoteState& getOldState()const {return oldState;}
    const NoteState& getNewState()const {return newState;}


    //a supprimer
    const QString& getNameRelation()const {return nameRelation;}
    const QString& getNameLabel() const {return nameLabel;}
    const NoteHolder& getNote1() const{return note1;}


};




class MementoCaretaker: public QObject{
   Q_OBJECT
   std::vector<Memento*> m_vecMemento; // pour le controle Z: annuler
   std::vector<Memento*> m_vecMementoInverse; // pour le controle Y: rétablir
   void save(Memento* memento);
public:
    MementoCaretaker(){}

public slots:
    void undo();
    void redo();

    void saveMementoRelation(const QString& nameR,const NoteHolder& n, const NoteHolder& n1,const QString& nameL) { save(new MementoRelation(nameR,n,n1,nameL)); std::cout<<"Enregistrement ok Relation memento"<<std::endl;}
    void saveMementoState(const NoteHolder& n, NoteState oldState, NoteState newState ) {save(new MementoNoteState(n,oldState,newState)); std::cout<<"Enregistrement ok State memento"<<std::endl;}


signals:
    void changeNoteState(const NoteHolder& n, NoteState nstate);

    void DeleteRelation(const QString& nameLabel,const NoteHolder& note,const NoteHolder& note1,const QString& nameRelation);
    void CreateRelation(const QString& nameLabel,const NoteHolder& note,const NoteHolder& note1,const QString& nameRelation);

};

#endif // MEMENTO_H
