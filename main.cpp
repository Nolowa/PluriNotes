#include <QCoreApplication>
#include <QTextStream>
#include <QTimer>
#include "notesmanager.h"
#include "version.h"
int main(int argc, char *argv[])
{
    /*créer des tables BD*/
    int version::rc=0;
    version::connectBd();


    QCoreApplication app(argc, argv);

    QTextStream qout(stdout);
    qout << "Demarrage" << endl;

    NotesManager m;

    qout << "Création de notes" << endl;
    Note& n1 = m.createNote();
    Note& n2 = m.createNote();
    Note& n3 = m.createNote();
    Note n4 = Sound(QUuid::createUuid(),QString("IVDEO.mp4")) ;

    qout << n1.getIdentifier().toString() << endl << n2.getIdentifier().toString() << endl << n3.getIdentifier().toString() << endl;
    qout <<n4.getIdentifier().toString()<< endl;
    qout << endl;
    qout <<n1.getCreated().toString()<< endl;
    n1.setTitle("Note de réunion");
    qout <<n1.getTitle()<< endl;



    qout << "Test de l'itérateur" << endl;

    Iterator<Note>& it = m.getIterator();
    while(!it.isDone()){
        it.next();
        qout << "Note : " << it.current().getIdentifier().toString() << endl;

    }

    QTimer::singleShot(5000, &app, SLOT(quit()));


    return app.exec();
}
