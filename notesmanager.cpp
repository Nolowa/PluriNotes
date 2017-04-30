#include "notesmanager.h"
#include <QException>

NotesManager::NotesManager()
{

}

Note& NotesManager::Iterator::current() const{
    if(idx == -1){
        AppException("NotesIterator points nothing").raise();
    }

    return manager.notes[idx];
}

bool NotesManager::Iterator::isDone() const{
    return idx >= 0 && idx >= manager.notes.size() - 1;
}

void NotesManager::Iterator::next(){
    if(!isDone()){
        idx++;
    }else{
        AppException("NotesIterator overflow attempt").raise();
    }
}

Note& NotesManager::createNote(){
    Note* note = new Note(QUuid::createUuid());

    notes.push_back(*note);

    return *note;
}

NotesManager::Iterator& NotesManager::getIterator(){
    return *(new NotesManager::Iterator(*this));
}
