#ifndef CORBEILLE_H
#define CORBEILLE_H
#include "notesmanager.h"


class Corbeille {
    Note** notes;
    int nbNotes;
    int nbMaxNotes;
    static Corbeille* instance;
    ~Corbeille(){}//privé pour empêcher son appel autrement que par l'intermédiaire de liberer_instance();
    Corbeille(const Corbeille& c);
    Corbeille& operator=(const Corbeille& c);
    Corbeille();
public:
    //-----------Question 3-----------//
    class Iterator {
        friend class Corbeille;
        Note** courant;
        int fin;
        Iterator(Note** deb, int f) :courant(deb), fin(f) {}
    public:
        bool isDone() const { return !fin; }
        void next() {
            if (isDone())
                throw new AppException("Fin");
            fin--;
            courant++;
        }

        Note* current()  const {
            if (isDone())
                throw new AppException("Fin");
            return *courant;
        }
    };
    Iterator getIterator() const { return Iterator(notes, nbNotes); }

    //-------------------------------//
    static Corbeille& get_instance();
    static void liberer_instance();

    void ajouterNote(Note* n);
    void vidage();
    void load_une(int id);
    void load_tout();/**< charger les notes sursis  */
};

#endif // CORBEILLE_H
