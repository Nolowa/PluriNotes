#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QVector>
#include "utils.h"
#include "note.h"
#include <iterator>

class NotesManager
{
    std::vector<Note> notes;



public:

    class Iterator : public ::Iterator<Note>{
        NotesManager& manager;
        int idx;

        Iterator();

    public:
        Iterator(NotesManager& m) : manager(m), idx(-1){};
        Note& current() const;
        bool isDone() const;
        void next();
    };

    NotesManager();
    Note& createNote();
    NotesManager::Iterator& getIterator();




};

#endif // NOTESMANAGER_H
