#include <QCoreApplication>
#include <QTextStream>
#include <QTimer>
#include <QTextCodec>
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
    Note n4 = Sound(QUuid::createUuid(),QString("IVDEO.mp4")) ;

    qout << n1.getIdentifier().toString() << endl << n2.getIdentifier().toString() << endl << n3.getIdentifier().toString() << endl;
    qout <<n4.getIdentifier().toString()<< endl;
    qout << endl;
    qout <<n1.getCreated().toString()<< endl;
    n1.setTitle("Note de réunion");
    qout <<n1.getTitle()<< endl;
    qout <<n1.getState()<<endl;
    n1.setState(sursis);
    qout <<n1.getState()<<endl;

    qout << "Création ARTICLE pour les tests" << endl;
    Article narticle= Article(QUuid::createUuid());
    narticle.setText("Cette article parle du projet de LO21 et du rapport que l'on doit réaliser après...");
    narticle.setTitle("LO21");
    qout <<"Etat de l'article: "<< narticle.getState() <<endl;
    qout <<"Titre de l'article: "<< narticle.getTitle() <<endl;
    qout <<"Corps de l'article: "<< narticle.getText() <<endl;
    narticle.setState(sursis);
    qout << "Nouvelle etat: " << narticle.getState() << endl;

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


    qout << "Nouvelle etat: " << ntask.getStatus() << endl;





    qout << "Test de l'itérateur" << endl;

    Iterator<Note>& it = m.getIterator();
    while(!it.isDone()){
        it.next();
        qout << "Note : " << it.current().getIdentifier().toString() << endl;

    }

    QTimer::singleShot(5000, &app, SLOT(quit()));


    return app.exec();
}
