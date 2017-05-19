#include "corbeille.h"
#include "version.h"
#include <QException>
#include <QTextStream>
Corbeille* Corbeille::instance=nullptr;
Corbeille::Corbeille():notes(nullptr),nbNotes(0),nbMaxNotes(0){}

Corbeille& Corbeille::get_instance() {
    if (!instance)
        instance = new Corbeille();
    return *instance;
}


void Corbeille::liberer_instance() {
    if (instance)
        delete instance;
    instance = nullptr;// conseillé
}


//Fin des membres statiques




void Corbeille::ajouterNote(Note* n) {
    for (int i = 0; i < nbNotes; i++) {
        if (notes[i]->getIdentifier() == n->getIdentifier()) throw new AppException("note déjà dans corbeille");
    }
    if (nbNotes == nbMaxNotes) {
        Note** newNotes = new Note*[nbNotes + 5];
        for (int i = 0; i < nbNotes; i++)
            newNotes[i] = notes[i];
        Note** oldNote = notes;
        notes = newNotes;
        nbMaxNotes += 5;
        delete[] oldNote;
        notes[nbNotes++] = n;
    }
    else {
        notes[nbNotes++] = n;
    }
    n->setState(sursis);
}

void Corbeille::vidage(){
    if(nbNotes){
        for (int i = 0; i < nbNotes; i++){
            /*supprimer ses versions*/
            size_t nombre=strlen(typeid(*notes[i]).name());
            int num=10;
            std::string nom=std::string(typeid(*notes[i]).name(),nombre);
            std::string nom1="class Article",nom2="class Image",nom3="class Task",nom4="class Sound",nom5="class Video";
            QString genre;
            if(!nom.compare(nom1)){num=0;genre="Article";}
            if(!nom.compare(nom2)){num=1;genre="Image";}
            if(!nom.compare(nom3)){num=2;genre="Task";}
            if(!nom.compare(nom4)){num=3;genre="Sound";}
            if(!nom.compare(nom5)){num=4;genre="Video";}

            QSqlQuery q;
            QString Id=notes[i]->getIdentifier().toString();
            q.exec("DELETE FROM  Note WHERE Id IN (SELECT Id FROM "+genre+" WHERE Idreal='"+Id+"') ");
            q.finish();
            q.exec("DELETE FROM  "+genre+" WHERE Idreal='"+Id+"'");
            q.finish();

            /*supprimer et liberer*/

            nbNotes--;

        }
        delete[] notes;
    }

}



