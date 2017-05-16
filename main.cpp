#include <QApplication>
#include <QtWidgets>
#include <QTextStream>
#include <QTimer>
#include "plurinotes.h"
#include "notesmanager.h"
#include "version.h"
#include "interfaces/noteslistview.h"

//include de test


int main(int argc, char *argv[]){
    //créer des tables BD

   /* QString name="test.db";
        version::connectBd(name);
        version::createTables();*/

    QApplication app(argc, argv);

    QTextStream qout(stdout);
    qout << "Demarrage" << endl;
    NotesManager& m=NotesManager::getInstance();



    //NotesListView nlv;
    qout << "Création de notes" << endl;


    Note& n3 = m.createNote();
    Note n4 = Sound(QUuid::createUuid(),QString("IVDEO.mp4")) ;

    NotesListView nlv(m);
    nlv.show();

    Note& n1 = m.createNote();
    n1.setTitle("Titre de la note 1");
    m.updateNote(n1);

    Note& n2 = m.createNote();
    n2.setTitle("Titre de la note 2");
    m.updateNote(n2);

    /*Article art(QUuid::createUuid());
    art.setTitle("un titre");*/

   /* NoteItem item(n1);
    item.show();*/

    /*NoteItem item2(art);
    item2.show();*/
/*
    RelationsManager<Note> relationsManager;
    Relationship<Note>& r1 = relationsManager.createRelation("UneRelationUnidirectionelle");
    Relationship<Note>& r2 = relationsManager.createRelation("UneRelationBidirectionelle", true);

    relationsManager.link(r1, n1, n3);
    relationsManager.link(r2, n1, n3);

    relationsManager.unlink(r1, n1, n3);
    qout << n1.getIdentifier().toString() << endl << n2.getIdentifier().toString() << endl << n3.getIdentifier().toString() << endl;


    qout << "Création TASK pour les tests" << endl;
    Task ntask= Task(QUuid::createUuid());
    ntask.setActionToBeDone("Finir le projet de LO21");
    ntask.setTitle("LO21");
    qout <<"Titre la tâche: "<< ntask.getTitle() <<endl;
    qout <<"Action de la tâche: "<< ntask.getActionToBeDone() <<endl;
    qout <<"Etat  de la tâche: "<< ntask.getStatus() <<endl;
    ntask.setStatus(terminee);
    qout << "Nouvelle etat: " << ntask.getExpired().toString() << endl;
    qout << "Priority: " << ntask.getPriority() << endl;
*/
/*
    qout << "Test de l'itérateur" << endl;*/
    Iterator<Note>& it = m.getIterator();
    while(!it.isDone()){
        it.next();
        qout << "Note : " << it.current().getIdentifier().toString() << endl;
        qout << "Titre : " << it.current().getTitle() << endl;
    }
    //QTimer::singleShot(5000, &app, SLOT(quit()));

 /*
     //Pour la création d'une note Type ARTICLE
    Article art(QUuid::createUuid());
    art.setTitle("Hello rWorld");
    art.setText("Hello World");
    qout << "Article title: " << art.getTitle() << endl;
    art.getInterface()->show();
*/
    //Test pour la Partie Graphique de la MainWindows #PluriNotes
   // PluriNotes fenetre(m);
    //fenetre.show();

/*
    //Pour la création d'une note Type TASK
    Task task(QUuid::createUuid());
    task.setPriority(3);
    task.setTitle("Hello World pour la tâche");
    task.setStatus(Status(2));
    QDateTime date=QDateTime::currentDateTime();
    task.setExpired(date);
    task.setActionToBeDone("FINIR LE PROJET DE LO21 A TEMPS ET MEME EN AVANCE SI POSSIBLE");
    task.getInterface()->show();

    //qout<< "status task = "<<task.getStatusInt()<<endl;
*/

/*
    //Pour la création d'une note Type IMAGE
    Image image(QUuid::createUuid());
    image.setDescription("Image d'une Galaxy");
    image.setTitle("Galaxy");
    //image.setImage("/Users/Thibault/Desktop/image.jpg");
    image.getInterface()->show();
*/

/*
    //Pour la création d'une note Type SOUND; Ne supporte que le format Wav
    Sound son(QUuid::createUuid());
    son.setDescription("Son modifié en Wav (prendre du Wav)");
    //son.setSoundFile("/Users/Thibault/Desktop/test.wav");
    son.setTitle("Son modifié");
    son.getInterface()->show();
*/

/*
   //Pour la création d'une note Type VIDEO
    Video video(QUuid::createUuid());
    video.setDescription("Video indéfini");
    video.setTitle("Vidéo Indéfini");
    //video.setNameVideoFile("/Users/Thibault/Desktop/test.mp4");
    video.getInterface()->show();
*/
    /*Task* t=new Task(ntask);
            version::insert(t);
            version::parcourir(t);*/
    return app.exec();
}
