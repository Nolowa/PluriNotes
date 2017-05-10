#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QVector>
#include <iterator>
#include "utils.h"
#include "note.h"
#include "image.h"
#include "article.h"
#include "video.h"
#include "task.h"
#include "sound.h"



class NotesManager{
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

    //~NotesManager();
};

#endif // NOTESMANAGER_H
