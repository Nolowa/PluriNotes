#include "corbeille.h"
#include "version.h"
#include <QException>

Corbeille::Corbeille(){}

/* Tout membre static  doit être définie dans un fichier source et initialisé */
Corbeille* Corbeille::instance=0;

Corbeille& Corbeille::getInstance(){
    if (!instance)// si pas encore d'instance de la classe
        instance= new Corbeille();// constructeur sans arguments
    return *instance;
}

void Corbeille::freeInstance(){
    if (instance)
        delete instance;
    instance=nullptr; // obligatoire
}

/*Fin des membres statiques*/


Note& Corbeille::Iterator::current() const{
    if(idx == -1){
        throw new AppException("Corbeille points nothing");
    }

    return manager.notes[idx];
}

bool Corbeille::Iterator::isDone() const{
    return idx >= 0 && idx >= manager.notes.size() - 1;
}

void Corbeille::Iterator::next(){
    if(!isDone()){
        idx++;
    }else{
        throw new AppException("NotesIterator overflow attempt");
    }
}

void Corbeille::ajouterNote(Note* n){
    Note* note = n;

    notes.push_back(nonte);

}

void Corbeille::vidage(){
    if(!notes.empty()){
        Note* note;
        for(note=notes.end()-1;note>=notes.begin();note--){
            /*supprimer ses versions*/
            size_t nombre=strlen(typeid(*note).name());
            int num=10;
            std::string nom=std::string(typeid(*note).name(),nombre);
            std::string nom1="class Article",nom2="class Image",nom3="class Task",nom4="class Sound",nom5="class Video";
            QString genre;
            if(!nom.compare(nom1)){num=0;genre="'Article'";}
            if(!nom.compare(nom2)){num=1;genre="'Image'";}
            if(!nom.compare(nom3)){num=2;genre="Task";}
            if(!nom.compare(nom4)){num=3;genre="'Sound'";}
            if(!nom.compare(nom5)){num=4;genre="'Video'";}

            QSqlQuery q;
            q.prepare("DELETE FROM Note, :Genre WHERE Note.Id = :Genre.Id AND :Genre.Idreal = :Id");
            q.bindValue(":Genre",genre);
            q.bindValue(":Id",note->getIdentifier());
            q.exec();
            q.finish();

            /*supprimer et liberer*/
            delete note;
            notes.pop_back();
        }
    }

}


Corbeille::Iterator& Corbeille::getIterator(){
    return *(new Corbeille::Iterator(*this));
}
