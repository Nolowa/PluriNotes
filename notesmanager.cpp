#include "notesmanager.h"
#include <QException>
#include <QApplication>
#include <QStyleFactory>
#include <iostream>

NotesManager::NotesManager(){

}

/* Tout membre static  doit être définie dans un fichier source et initialisé */
NotesManager* NotesManager::instance=0;

NotesManager& NotesManager::getInstance(){
    if (!instance)// si pas encore d'instance de la classe
        instance= new NotesManager();// constructeur sans arguments
    return *instance;
}

void NotesManager::freeInstance(){
    if (instance)
        delete instance;
    instance=nullptr; // obligatoire
}

/*Fin des membres statiques*/


Note& NotesManager::Iterator::current() const{
    if(idx == -1){
        throw new AppException("NotesIterator points nothing");
    }

    //return dynamic_cast<Note&>(*(manager.notesModel->item(idx)));
    return *(manager.notes[idx]);
}

bool NotesManager::Iterator::isDone() const{
    //return idx >= 0 && idx >= manager.notesModel->rowCount() - 1;
    return idx >= 0 && idx >= manager.notes.size() - 1;
}

void NotesManager::Iterator::next(){
    if(!isDone()){
        idx++;
    }else{
        throw new AppException("NotesIterator overflow attempt");
    }
}

Note& NotesManager::createNote(){
    Note* note = new Note(QUuid::createUuid());

    notes.push_back(note);

    emit noteCreated(*note);

    return *note;
}

Note& NotesManager::updateNote(Note& note){
    // TODO : Ré-injecter la note dans la mémoire
    // TODO : Trigger UPDATE base de données
    // TODO : Trigger GUI updates
    std::cout << endl << "note received update" << endl;
    emit noteUpdated(note);
}
/*
int NotesManager::getPosition(Note& note) const{
    int i = 0;
    Iterator it = this->getIterator();
    while(!it.isDone()){
        it.next();

        if(it.current().getIdentifier() == note.getIdentifier()){
            return i;
        }
        i++;
    }
}*/

NotesManager::Iterator& NotesManager::getIterator() const{
    Iterator* it = new NotesManager::Iterator(*this);
    return *it;
}
