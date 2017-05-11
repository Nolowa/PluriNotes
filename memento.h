#ifndef MEMENTO_H
#define MEMENTO_H
#include "notesmanager.h"
#include<vector>
class Memento
{
    Note* m_note;
    /*
    QUuid m_identifier;
    QString m_title;
    enum m_state {active, non_editable,sursis};
    QDateTime m_created;
    QDateTime m_edited;*/
    /*ci dessus sont l'info dans Note*/
   /* QString m_texte;//article
    QString m_description;//Image, video, audio
    QString m_actionFaire;//Tache*/
    /*il manque encore fichier et tache*/
public:
    //Memento(const Note& n){ m_note = new Note(p); } // le p ne fonctionne pas.
    Memento();
    Memento& operator=(const Memento &memento)
      {
          m_note = memento.m_note;
          return *this;
      }
};

class MementoCaretaker {
   std::vector<Memento> m_vecMemento;

public:
    MementoCaretaker();
    Memento Load(int state) {
        return m_vecMemento[state];;
    }

    void Save(Memento memento) {
        m_vecMemento.push_back(memento);
    }
};

#endif // MEMENTO_H
