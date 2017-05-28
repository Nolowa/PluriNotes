#ifndef CORBEILLE_H
#define CORBEILLE_H
#include "notesmanager.h"


class Corbeille : public QObject{
    Note** notes;
    int nbNotes;
    int nbMaxNotes;
    static Corbeille* instance;
    ~Corbeille(){}//privé pour empêcher son appel autrement que par l'intermédiaire de liberer_instance();
    Corbeille(const Corbeille& c);
    Corbeille& operator=(const Corbeille& c);
    Corbeille();

    Q_OBJECT
public:
    int getNbNotes()const{return nbNotes;}
    const Note* find(const QUuid& identifier) const;

    //Iterator//
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

        Note& current()  const {
            if (isDone())
                throw new AppException("Fin");
            return **courant;
        }
    };
    Iterator getIterator() const { return Iterator(notes, nbNotes); }

    //-------------------------------//
    static Corbeille& get_instance();
    static void liberer_instance();

    void pushNote(Note* n);/**< ajouter une note dans corbeille  */
    void load_une(int id);/**< facilite load_tout  */
    void load_tout();/**< charger les notes sursis  */
signals:

    void noteCreatedc(const Note&);
    void supprimer(const Note*);
    void noteUpdated(const Note&);
public slots:
    void ajouterNote(Note* n);/**< ajouter une nouvelle note dans corbeille et set valeur sursis de ses versions  */
    void vidage();
    //void activer(Note *);
};

#endif // CORBEILLE_H
