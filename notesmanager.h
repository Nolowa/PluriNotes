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

    void registerNewNote(Note* note);

    //int getPosition(Note& note) const;

    Q_OBJECT

public:
    static NotesManager& getInstance();
    static void freeInstance();




    const Note* find(const QUuid& identifier) const;

    void load(); // load notes from file filename

    void load_affiche(); // load les notes dernieres from BBD et puis afficher ses id title...
    void save() const; // save notes in BBD
    void load_vrai(int id);//à travers de l'interface on sait excatement l'id de note qu'on veut charger


    Note& updateNote(Note& note);


    class Iterator : public ::Iterator<Note>{
        const NotesManager& manager;
        int idx;
        Iterator();
    public:
        Iterator(const NotesManager& m) : manager(m), idx(-1){}
        Note& current() const;
        bool isDone() const;
        void next();

    };

    NotesManager::Iterator& getIterator() const;

signals:

    void noteCreated(const Note&);

    void noteUpdated(const Note&);

public slots:
    const Article& createArticle();
    const Task& createTask();
    const Image& createImage();
    const Sound& createSound();
    const Video& createVideo();


   // ~NotesManager();
};

#endif // NOTESMANAGER_H
