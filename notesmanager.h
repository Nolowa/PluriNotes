#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QVector>
#include <iterator>
#include <QStandardItemModel>
#include <QModelIndex>
#include "utils.h"
#include "notes/note.h"
#include "notes/image.h"
#include "notes/article.h"
#include "notes/video.h"
#include "notes/task.h"
#include "notes/sound.h"
#include "relations/relationsmanager.h"


class NotesManager : public QObject{
public:

    class NotesModelHolder
    {
        NotesManager& notesManager;
        QStandardItemModel model;
        QMap<QUuid, QModelIndex> indexMap;

        //void generateModel(NotesManager&);
        QStandardItem* generateItem(const Note&);
        void updateItem(QStandardItem*, const Note&);
        void updateItem(const Note& note);

        friend class NotesManager;

    public:
        NotesModelHolder(NotesManager& nm) : notesManager(nm){}
        QStandardItemModel& getModel(){ return model; }
        const Note* findByIndex(QModelIndex&) const;

    };

private:
    std::vector<const Note*> notes;
    Note** notess;
    QString filename;
    NotesModelHolder* modelHolder;

    static NotesManager* instance;// singleton
    NotesManager();
    NotesManager(const NotesManager& n);
    NotesManager& operator=(const NotesManager& n);

    void registerNewNote(Note* note);

    Q_OBJECT

public:
    static NotesManager& getInstance();
    static void freeInstance();

    const Note* find(const QUuid& identifier) const;
    NotesModelHolder & getModelHolder() const { return *modelHolder; }

    void load(); // load notes from file filename

    void load_vrai(int id);//à travers de l'interface on sait excatement l'id de note qu'on veut charger
    void load_version();/**< load toutes les notes de versions dernières dans notemanagers*/


    class Iterator : public ::Iterator<const Note>{
        const NotesManager& manager;
        int idx;
        Iterator();
    public:
        Iterator(const NotesManager& m) : manager(m), idx(-1){}
        const Note& current() const;
        bool isDone() const;
        void next();

    };


    NotesManager::Iterator& getIterator() const;

    bool replaceReference(const Note *);

signals:

    void noteCreated(const Note&);
    void noteUpdated(const Note&);

public slots:
    const Article& createArticle();
    const Task& createTask();
    const Image& createImage();
    const Sound& createSound();
    const Video& createVideo();
    void updateNote(const Note * note);


   // ~NotesManager();
};

#endif // NOTESMANAGER_H
