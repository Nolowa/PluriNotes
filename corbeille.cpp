#include "corbeille.h"
#include "version.h"
#include <QException>
#include <QTextStream>
QTextStream qout(stdout);
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
    QSqlQuery q;
    QSqlQuery q1;
    size_t nombre=strlen(typeid(*n).name());
    std::string nom=std::string(typeid(*n).name(),nombre);
    std::string nom1="class Article",nom2="class Image",nom3="class Task",nom4="class Sound",nom5="class Video";
    std::cout<<nom;
    if(!nom.compare(nom1)){
        q.exec("SELECT n.Id FROM (Note n INNER JOIN Article a ON n.Id=a.Id) WHERE a.Idreal='"+ n->getIdentifier().toString()+"';");
        while(q.next()){
            q1.exec("UPDATE Note SET State = 'sursis' WHERE Id="+q.value(0).toString()+";");
        }
    }
    if(!nom.compare(nom2)){
        q.exec("SELECT n.Id FROM (Note n INNER JOIN Image a ON n.Id=a.Id) WHERE a.Idreal='"+ n->getIdentifier().toString()+"';");
        while(q.next()){
            q1.exec("UPDATE Note SET State = 'sursis' WHERE Id="+q.value(0).toString()+";");
        }
    }
    if(!nom.compare(nom3)){
        q.exec("SELECT n.Id FROM (Note n INNER JOIN Task a ON n.Id=a.Id) WHERE a.Idreal='"+ n->getIdentifier().toString()+"';");
        while(q.next()){
            q1.exec("UPDATE Note SET State = 'sursis' WHERE Id="+q.value(0).toString()+";");
        }
    }
    if(!nom.compare(nom4)){
        q.exec("SELECT n.Id FROM (Note n INNER JOIN Sound a ON n.Id=a.Id) WHERE a.Idreal='"+ n->getIdentifier().toString()+"';");
        while(q.next()){
            q1.exec("UPDATE Note SET State = 'sursis' WHERE Id="+q.value(0).toString()+";");
        }
    }
    if(!nom.compare(nom5)){
        q.exec("SELECT n.Id FROM (Note n INNER JOIN Video a ON n.Id=a.Id) WHERE a.Idreal='"+ n->getIdentifier().toString()+"';");
        while(q.next()){
            q1.exec("UPDATE Note SET State = 'sursis' WHERE Id="+q.value(0).toString()+";");
        }
    }
}

void Corbeille::vidage(){
    if(nbNotes){
        for (int i = 0; i < nbNotes; i++){
            /*supprimer ses versions*/
            size_t nombre=strlen(typeid(*notes[i]).name());
            int num=10;
            std::string nom=std::string(typeid(*notes[i]).name(),nombre);
            QString genre;
            if(!nom.compare("class Article")){num=0;genre="Article";}
            if(!nom.compare("class Image")){num=1;genre="Image";}
            if(!nom.compare("class Task")){num=2;genre="Task";}
            if(!nom.compare("class Sound")){num=3;genre="Sound";}
            if(!nom.compare("class Video")){num=4;genre="Video";}

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

void Corbeille::load_une(int id){
    QSqlQuery q;
    q.exec("SELECT * FROM Note WHERE Id='"+ QString::number(id) +"';");
    q.next();
    QString State=q.value(5).toString();
    QString etat1="active",etat2="sursis",etat3="non_editable";
    int numm=-1;
    if(!State.compare(etat1)){numm=1;}
    if(!State.compare(etat2)){numm=2;}
    if(!State.compare(etat3)){numm=3;}
    //q.finish();
    QString Genre=q.value(1).toString();
    QString nom1="Article",nom2="Image",nom3="Task",nom4="Sound",nom5="Video";
    QSqlQuery q1;
    if(!Genre.compare(nom1)){//Article
        q1.exec("SELECT * FROM Article WHERE Id='"+ QString::number(id) +"';");
        q1.next();
        QString Idreal1=q1.value(1).toString();
        QString Title1=q.value(2).toString();
        QDateTime Created1=q.value(3).toDateTime();
        QString Text=q1.value(2).toString();
        Article* nouveau_a=new Article(QUuid(Idreal1),Created1);
        nouveau_a->setTitle(Title1);
        nouveau_a->setText(Text);
        switch(numm){
        case 1:nouveau_a->setState(active);break;
        case 2:nouveau_a->setState(sursis);break;
        case 3:nouveau_a->setState(non_editable);break;
        }
        Note* note1=static_cast<Note*>(nouveau_a);
        ajouterNote(note1);
    }
    if(!Genre.compare(nom2)){//Image
        q1.exec("SELECT * FROM Image WHERE Id='"+ QString::number(id) +"';");
        q1.next();
        QString Idreal2=q1.value(1).toString();
        QString Description2=q1.value(2).toString();
        QString Title2=q.value(2).toString();
        QDateTime Created2=q.value(3).toDateTime();
        Image* nouveau_i=new Image(QUuid(Idreal2),Created2);
        nouveau_i->setTitle(Title2);
        switch(numm){
        case 1:nouveau_i->setState(active);break;
        case 2:nouveau_i->setState(sursis);break;
        case 3:nouveau_i->setState(non_editable);break;
        }
        nouveau_i->setDescription(Description2);
        Note* note2=static_cast<Note*>(nouveau_i);
        ajouterNote(note2);
    }
    if(!Genre.compare(nom3)){//Task
        q1.exec("SELECT * FROM Task WHERE Id='"+ QString::number(id) +"';");
        q1.next();
        QString Idreal3=q1.value(1).toString();
        QString Title3=q.value(2).toString();
        QDateTime Created3=q.value(3).toDateTime();
        QString ActionToBeDone3=q1.value(2).toString();
        QString Status=q1.value(3).toString();
        unsigned int Priority=q1.value(4).toInt();
        QDateTime Expired3=q.value(5).toDateTime();
        Task* nouveau_t=new Task(QUuid(Idreal3),Created3);
        nouveau_t->setTitle(Title3);
        nouveau_t->setActionToBeDone(ActionToBeDone3);
        nouveau_t->setPriority(Priority);
        nouveau_t->setExpired(Expired3);
        switch(numm){
        case 1:nouveau_t->setState(active);break;
        case 2:nouveau_t->setState(sursis);break;
        case 3:nouveau_t->setState(non_editable);break;
        }
        if(Status=="en_attente"){nouveau_t->setStatus(en_attente);}
        if(Status=="en_cours"){nouveau_t->setStatus(en_cours);}
        if(Status=="terminee"){nouveau_t->setStatus(terminee);}
        Note* note3=static_cast<Note*>(nouveau_t);
        ajouterNote(note3);
    }
    if(!Genre.compare(nom4)){//Sound
        q1.exec("SELECT * FROM Sound WHERE Id='"+ QString::number(id) +"';");
        q1.next();
        QString Idreal4=q1.value(1).toString();
        QString Description4=q1.value(2).toString();
        QString Title4=q.value(2).toString();
        QDateTime Created4=q.value(3).toDateTime();
        QString File4=q1.value(3).toString();
        Sound* nouveau_s=new Sound(QUuid(Idreal4),Created4,File4);
        nouveau_s->setTitle(Title4);
        switch(numm){
        case 1:nouveau_s->setState(active);break;
        case 2:nouveau_s->setState(sursis);break;
        case 3:nouveau_s->setState(non_editable);break;
        }
        nouveau_s->setDescription(Description4);
        Note* note4=static_cast<Note*>(nouveau_s);
        ajouterNote(note4);
    }
    if(!Genre.compare(nom5)){//Video
        q1.exec("SELECT * FROM Video WHERE Id='"+ QString::number(id) +"';");
        q1.next();
        QString Idreal5=q1.value(1).toString();
        QString Description5=q1.value(2).toString();
        QString Title5=q.value(2).toString();
        QDateTime Created5=q.value(3).toDateTime();
        QString File5=q1.value(3).toString();
        Video* nouveau_v=new Video(QUuid(Idreal5),Created5,File5);
        nouveau_v->setTitle(Title5);
        switch(numm){
        case 1:nouveau_v->setState(active);break;
        case 2:nouveau_v->setState(sursis);break;
        case 3:nouveau_v->setState(non_editable);break;
        }
        nouveau_v->setDescription(Description5);
        Note* note5=static_cast<Note*>(nouveau_v);
        ajouterNote(note5);
    }
}

void Corbeille::load_tout(){
    QSqlQuery q;
    q.exec("SELECT n.Id,max(n.Edited) FROM (Note n INNER JOIN Article a ON n.Id=a.Id)WHERE n.State='sursis' GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_une(Id);
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Image a ON n.Id=a.Id)WHERE n.State='sursis' GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_une(Id);
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Task a ON n.Id=a.Id)WHERE n.State='sursis' GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_une(Id);
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Video a ON n.Id=a.Id)WHERE n.State='sursis' GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_une(Id);
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Sound a ON n.Id=a.Id)WHERE n.State='sursis' GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_une(Id);
    }
    q.finish();
}



