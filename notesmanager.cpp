#include "notesmanager.h"
#include <QException>
#include <QApplication>
#include <QStyleFactory>
#include <iostream>
#include "version.h"
NotesManager::NotesManager(){

}

/* Tout membre static  doit être définie dans un fichier source et initialisé */
NotesManager* NotesManager::instance=0;

NotesManager& NotesManager::getInstance(){
    if (!instance)// si pas encore d'instance de la classe
        instance= new NotesManager();// constructeur sans arguments
    return *instance;
}

void NotesManager::freeInstance(){
    if (instance)
        delete instance;
    instance=nullptr; // obligatoire
}

/*Fin des membres statiques*/


const Note& NotesManager::Iterator::current() const{
    if(idx == -1){
        throw new AppException("NotesIterator points nothing");
    }

    //return dynamic_cast<Note&>(*(manager.notesModel->item(idx)));
    return *(manager.notes[idx]);
}

bool NotesManager::Iterator::isDone() const{
    //return idx >= 0 && idx >= manager.notesModel->rowCount() - 1;
    int size = manager.notes.size();
    return /*idx >= 0 && */idx >= size - 1;
}

void NotesManager::Iterator::next(){
    if(!isDone()){
        idx++;
    }else{
        throw new AppException("NotesIterator overflow attempt");
    }
}

const Note* NotesManager::find(const QUuid& identifier) const{
    Iterator& it = getIterator();
    while(!it.isDone()){
        it.next();
        const Note& current = it.current();
        if(current.getIdentifier() == identifier){
            return &current;
        }
    }

    return nullptr;
}

/*Note& NotesManager::createNote(){
    Article* note = new Article(QUuid::createUuid());

    notes.push_back(note);

    emit noteCreated(*note);

    return *note;
}*/

void NotesManager::registerNewNote(Note * note){
    notes.push_back(note);
    emit noteCreated(*note);
}

const Article& NotesManager::createArticle(){
    Article * a = new Article();
    registerNewNote(a);
    return *a;
}

const Task& NotesManager::createTask(){
    Task * a = new Task();
    registerNewNote(a);
    return *a;
}

const Image& NotesManager::createImage(){
    Image * a = new Image();
    registerNewNote(a);
    return *a;
}

const Video& NotesManager::createVideo(){
    Video * a = new Video();
    registerNewNote(a);
    return *a;
}

const Sound& NotesManager::createSound(){
    Sound * a = new Sound();
    registerNewNote(a);
    return *a;
}

bool NotesManager::replaceReference(const Note * n){
    for(int i = 0; i < notes.size(); i++){
        if(notes[i]->getIdentifier() == n->getIdentifier()){
            notes[i] = n;
            return true;
        }
    }

    return false;
}

void NotesManager::updateNote(const Note * note){
    // TODO : Ré-injecter la note dans la mémoire
    // TODO : Trigger UPDATE base de données
    // TODO : Trigger GUI updates
    replaceReference(note);
    std::cout << std::endl << "note received update" << std::endl;
    emit noteUpdated(*note);
}

NotesManager::Iterator& NotesManager::getIterator() const{
    Iterator* it = new NotesManager::Iterator(*this);
    return *it;
}


void NotesManager::save() const{
    Iterator& it=this->getIterator();
    while(!it.isDone()){
        it.next();
        version::insert(&it.current());
    }
}

/***************************************************************/
/* TODO : Cette fonction ne devrait pas être dans NotesManager */
/***************************************************************/

void NotesManager::load_affiche(){
    /*extraire les dernieres versions*/
    QSqlQuery q;
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Article a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            QString Id = q.value(0).toString();
            QString Genre = q.value(1).toString();
            QString Title = q.value(2).toString();
            QString Edited = q.value(3).toString();
            qDebug() <<"Id: "<< Id <<"Genre: " <<Genre<< "Title: "<<Title<<"Edited: "<<Edited ;
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Image a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            QString Id = q.value(0).toString();
            QString Genre = q.value(1).toString();
            QString Title = q.value(2).toString();
            QString Edited = q.value(3).toString();
            qDebug() <<"Id: "<< Id <<"Genre: " <<Genre<< "Title: "<<Title<<"Edited: "<<Edited ;
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Task a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            QString Id = q.value(0).toString();
            QString Genre = q.value(1).toString();
            QString Title = q.value(2).toString();
            QString Edited = q.value(3).toString();
            qDebug() <<"Id: "<< Id <<"Genre: " <<Genre<< "Title: "<<Title<<"Edited: "<<Edited ;
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Video a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            QString Id = q.value(0).toString();
            QString Genre = q.value(1).toString();
            QString Title = q.value(2).toString();
            QString Edited = q.value(3).toString();
            qDebug() <<"Id: "<< Id <<"Genre: " <<Genre<< "Title: "<<Title<<"Edited: "<<Edited ;
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Sound a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            QString Id = q.value(0).toString();
            QString Genre = q.value(1).toString();
            QString Title = q.value(2).toString();
            QString Edited = q.value(3).toString();
            qDebug() <<"Id: "<< Id <<"Genre: " <<Genre<< "Title: "<<Title<<"Edited: "<<Edited ;
    }
    q.finish();
}


/***************************************************************/
/* TODO : Cette fonction ne devrait pas être dans NotesManager */
/***************************************************************/
void NotesManager::load_vrai(int id){
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
        notes.push_back(note1);
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
        notes.push_back(note2);
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
        notes.push_back(note3);
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
        notes.push_back(note4);
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
        notes.push_back(note5);
    }
}

void NotesManager::load_version(){
    QSqlQuery q;
    q.exec("SELECT n.Id,max(n.Edited) FROM (Note n INNER JOIN Article a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_vrai(Id);
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Image a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_vrai(Id);
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Task a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_vrai(Id);
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Video a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_vrai(Id);
    }
    q.finish();
    q.exec("SELECT n.Id,n.Genre,n.Title,max(n.Edited) FROM (Note n INNER JOIN Sound a ON n.Id=a.Id) GROUP BY a.Idreal;");
    while (q.next()) {
            int Id = q.value(0).toInt();
            load_vrai(Id);
    }
    q.finish();
}


