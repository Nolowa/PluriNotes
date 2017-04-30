#include <QCoreApplication>
#include <QTextStream>
#include <QTimer>
#include "notesmanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTextStream qout(stdout);
    qout << "Demarrage" << endl;

    NotesManager m;

    qout << "Création de notes" << endl;
    Note& n1 = m.createNote();
    Note& n2 = m.createNote();
    Note& n3 = m.createNote();

    qout << n1.getIdentifier().toString() << endl << n2.getIdentifier().toString() << endl << n3.getIdentifier().toString() << endl;
    qout << endl;

    qout << "Test de l'itérateur" << endl;

    Iterator<Note>& it = m.getIterator();
    while(!it.isDone()){
        it.next();
        qout << "Note : " << it.current().getIdentifier().toString() << endl;

    }

    QTimer::singleShot(5000, &app, SLOT(quit()));


    return app.exec();
}
