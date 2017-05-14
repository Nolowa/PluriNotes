#ifndef CORBEILLE_H
#define CORBEILLE_H
#include "notesmanager.h"

class Corbeille
{
    std::vector<Note*> notes;


    static Corbeille* instance;// singleton
    Corbeille();
    Corbeille(const Corbeille& n);
    Corbeille& operator=(const Corbeille& n);

public:
    corbeille();
    static Corbeille& getInstance();
    static void freeInstance();

    class Iterator : public ::Iterator<Note>{
        Corbeille& manager;
        int idx;
        Iterator();
    public:
        Iterator(Corbeille& m) : manager(m), idx(-1){};
        Note& current() const;
        bool isDone() const;
        void next();
    };

    Corbeille::Iterator& getIterator();
    static void ajouterNote(Note* n);
    static void vidage();


};

#endif // CORBEILLE_H
