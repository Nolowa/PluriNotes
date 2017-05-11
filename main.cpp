#include <QApplication>
#include <QtWidgets>
#include <QTextStream>
#include <QTimer>
#include "plurinotes.h"
#include "notesmanager.h"

#include "version.h"
int main(int argc, char *argv[]){
   /* //créer des tables BD
    int version::rc=0;
    version::connectBd();
   */
    QApplication app(argc, argv);

    QTextStream qout(stdout);
    qout << "Demarrage" << endl;
    NotesManager& m=NotesManager::getInstance();

    qout << "Création de notes" << endl;
    Note& n1 = m.createNote();
    Note& n2 = m.createNote();
    Note& n3 = m.createNote();
    Note n4 = Sound(QUuid::createUuid(),QString("IVDEO.mp4")) ;

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


    qout << "Test de l'itérateur" << endl;
    Iterator<Note>& it = m.getIterator();
    while(!it.isDone()){
        it.next();
        qout << "Note : " << it.current().getIdentifier().toString() << endl;
    }
    //QTimer::singleShot(5000, &app, SLOT(quit()));

//    Article art(QUuid::createUuid());
//    art.setTitle("Hello World");
//    art.setText("Hello World");
//    qout << "Article title: " << art.getTitle() << endl;
//    art.show();

    //Test pour la Partie Graphique de la MainWindows #PluriNotes
   // PluriNotes fenetre(m);
    //fenetre.show();

    return app.exec();
}
