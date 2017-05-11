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
    Note** notess;
    QString filename;

    static NotesManager* instance;// singleton
    NotesManager();
    NotesManager(const NotesManager& n);
    NotesManager& operator=(const NotesManager& n);

public:
    static NotesManager& getInstance();
    static void freeInstance();

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


    Note& createNote();
    NotesManager::Iterator& getIterator();

   // ~NotesManager();
};

#endif // NOTESMANAGER_H
