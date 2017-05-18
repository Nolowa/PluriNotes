#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QVector>
#include <iterator>
#include <QStringListModel>
#include "utils.h"
#include "notes/note.h"
#include "notes/image.h"
#include "notes/article.h"
#include "notes/video.h"
#include "notes/task.h"
#include "notes/sound.h"
#include "relations/relationsmanager.h"


class NotesManager : public QObject{
    std::vector<Note*> notes;
    Note** notess;
    QString filename;

    static NotesManager* instance;// singleton
    NotesManager();
    NotesManager(const NotesManager& n);
    NotesManager& operator=(const NotesManager& n);

    //int getPosition(Note& note) const;

    Q_OBJECT

public:
    static NotesManager& getInstance();
    static void freeInstance();

    class Iterator : public ::Iterator<Note>{
        const NotesManager& manager;
        int idx;
        Iterator();
    public:
        Iterator(const NotesManager& m) : manager(m), idx(-1){};
        Note& current() const;
        bool isDone() const;
        void next();

    };

    const Note* find(const QUuid& identifier) const;

    void load(); // load notes from file filename
    void save() const; // save notes in file filename
    Note& createNote();
    NotesManager::Iterator& getIterator() const;

    //QStandardItemModel& getTitleModel();

    Note& updateNote(Note& note);

signals:

    void noteCreated(const Note&);

    void noteUpdated(const Note&);


   // ~NotesManager();
};

#endif // NOTESMANAGER_H
