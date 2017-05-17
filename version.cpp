#include "version.h"
QSqlDatabase version::db = QSqlDatabase::addDatabase("QSQLITE");
int version::table_exist=0;
int version::open=0;
bool version::connectBd(const QString& dbname){
    db.setDatabaseName(dbname);
    if(db.open())
    {
        std::cout << "Vous êtes maintenant connecté à " << q2c(db.hostName()) << std::endl;
        open=1;
        return true;
    }
    else
    {
        std::cout << "La connexion a échouée, désolé" << std::endl;
        return false;
    }
}

void version::closeBd(){
    db.close();
    open=0;
}
void version::createTables(){
        QSqlQuery query;
        bool result = query.exec("CREATE TABLE IF NOT EXISTS Note (Id INTEGER PRIMARY KEY   AUTOINCREMENT,Genre VARCHAR(20) NOT NULL, Title VARCHAR(20) ,Created TEXT, Edited TEXT,State VARCHAR(20));");
        if(result)
        {
            std::cout << "table Note crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table note" << std::endl << q2c(query.lastError().text()) << std::endl;
        }
        bool result1 = query.exec("CREATE TABLE IF NOT EXISTS Article (Id INTEGER NOT NULL,Idreal VARCHAR NOT NULL,Text TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id) ON DELETE CASCADE);");
        if(result1)
        {
            std::cout << "table Article crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table Article" << std::endl << q2c(query.lastError().text()) << std::endl;
        }
        bool result2 = query.exec("CREATE TABLE IF NOT EXISTS Image (Id INTEGER NOT NULL,Idreal VARCHAR NOT NULL,Description TEXT ,File TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);");
        if(result2)
        {
            std::cout << "table Image crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table Image" << std::endl << q2c(query.lastError().text()) << std::endl;
        }
        bool result3 = query.exec("CREATE TABLE IF NOT EXISTS Task (Id INTEGER NOT NULL,Idreal VARCHAR NOT NULL,ActionToBeDone TEXT ,Status VARCHAR(20) ,Priority INT(1) ,"
                                  "Expired TEXT , PRIMARY KEY (Id), FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);");
        if(result3)
        {
            std::cout << "table Task crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table Task" << std::endl << q2c(query.lastError().text()) << std::endl;
        }
        bool result4 = query.exec("CREATE TABLE IF NOT EXISTS Sound (Id INTEGER NOT NULL,Idreal VARCHAR NOT NULL,Description TEXT ,File TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);");
        if(result4)
        {
            std::cout << "table Sound crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table Sound" << std::endl << q2c(query.lastError().text()) << std::endl;
        }
        bool result5 = query.exec("CREATE TABLE IF NOT EXISTS Video (Id INTEGER NOT NULL,Idreal VARCHAR NOT NULL,Description TEXT ,File TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);");
        if(result5)
        {
            std::cout << "table Video crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table Video" << std::endl << q2c(query.lastError().text()) << std::endl;
        }


}

void version::insert(Note* n){
    /*verifier le type de n*/
    size_t nombre=strlen(typeid(*n).name());
    int num=10;
    std::string nom=std::string(typeid(*n).name(),nombre);
    std::string nom1="class Article",nom2="class Image",nom3="class Task",nom4="class Sound",nom5="class Video";
    QString genre;
    if(!nom.compare(nom1)){num=0;genre="Article";}
    if(!nom.compare(nom2)){num=1;genre="Image";}
    if(!nom.compare(nom3)){num=2;genre="Task";}
    if(!nom.compare(nom4)){num=3;genre="Sound";}
    if(!nom.compare(nom5)){num=4;genre="Video";}
    //std::cout<<nom <<"  "<<nom.compare(nom3)<<std::endl;

    /*insert into note*/
    QSqlQuery q;
    q.prepare("INSERT INTO Note(Genre,Title,Created,Edited,State) VALUES (:Genre,:Title,:Created,:Edited,:State)");
    q.bindValue(":Genre",genre);
    q.bindValue(":Title",n->getTitle());
    q.bindValue(":Created",n->getCreated());
    q.bindValue(":Edited",n->getEdited());
    q.bindValue(":State",n->getState());
    q.exec();
    /*obetenir le id généré*/
    int id=q.lastInsertId().toInt();
    q.finish();

    std::cout<<"id"<<id<<std::endl;
    /*insert into table dérivée*/
    QSqlQuery q1;
    switch (num) {
    case 0://Article
        Article* nouveau_a;
        nouveau_a=static_cast<Article*>(n);
        q1.prepare("INSERT INTO Article (Id,Idreal,Text) VALUES (:Id,:Idreal,:Text)");
        q1.bindValue(":Id",id);
        q1.bindValue(":Idreal",nouveau_a->getIdentifier());
        q1.bindValue(":Text",nouveau_a->getText());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }
        q1.finish();
        break;
    case 1://Image
        Image* nouveau_i;
        nouveau_i=static_cast<Image*>(n);
        q1.prepare("INSERT INTO Image (Id,Idreal,Description,File) VALUES (:Id,:Idreal,:Description,'file')");
        q1.bindValue(":Id",id);
        q1.bindValue(":Idreal",nouveau_i->getIdentifier());
        q1.bindValue(":Description",nouveau_i->getDescription());
        //q1.bindValue(":File",nouveau_i->getFile());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }
        q1.finish();
        break;
    case 2://Task
        Task* nouveau_t;
        nouveau_t=static_cast<Task*>(n);
        q1.prepare("INSERT INTO Task (Id,Idreal,ActionToBeDone,Status,Priority,Expired) VALUES (:Id,:Idreal,:ActionToBeDone,:Status,:Priority,:Expired)");
        q1.bindValue(":Id",id);
        q1.bindValue(":Idreal",nouveau_t->getIdentifier());
        q1.bindValue(":ActionToBeDone",nouveau_t->getActionToBeDone());
        q1.bindValue(":Status",nouveau_t->getStatus_re());
        q1.bindValue(":Priority",nouveau_t->getPriority());
        q1.bindValue(":Expired",nouveau_t->getExpired());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }
        q1.finish();


        break;
    case 3:
        Sound* nouveau_s;
        nouveau_s=static_cast<Sound*>(n);
        q1.prepare("INSERT INTO Sound (Id,Idreal,Description,File) VALUES (:Id,:Idreal,:Description,'file')");
        q1.bindValue(":Id",id);
        q1.bindValue(":Idreal",nouveau_s->getIdentifier());
        q1.bindValue(":Description",nouveau_s->getDescription());
        //q1.bindValue(":File",nouveau_s->getFile());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }
        q1.finish();

        break;
    case 4:
        Video* nouveau_v;
        nouveau_v=static_cast<Video*>(n);
        q1.prepare("INSERT INTO Video (Id,Idreal,Description,File) VALUES (:Id,:Idreal,:Description,'file')");
        q1.bindValue(":Id",id);
        q1.bindValue(":Idreal",nouveau_v->getIdentifier());
        q1.bindValue(":Description",nouveau_v->getDescription());
        //q1.bindValue(":File",nouveau_v->getFile());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }
        q1.finish();

        break;
    }
}

void version::parcourir(Note* n){
    /*verifier le type de n*/
    size_t nombre=strlen(typeid(*n).name());
    int num=10;
    std::string nom=std::string(typeid(*n).name(),nombre);
    std::string nom1="class Article",nom2="class Image",nom3="class Task",nom4="class Sound",nom5="class Video";
    QString genre;
    if(!nom.compare(nom1)){num=0;genre="Article";}
    if(!nom.compare(nom2)){num=1;genre="Image";}
    if(!nom.compare(nom3)){num=2;genre="Task";}
    if(!nom.compare(nom4)){num=3;genre="Sound";}
    if(!nom.compare(nom5)){num=4;genre="Video";}


    QSqlQuery q1;
    switch (num) {
    case 0://Article
        Article* nouveau_a;
        nouveau_a=static_cast<Article*>(n);
        q1.prepare("SELECT * FROM Article WHERE Idreal=:Id");
        q1.bindValue(":Id",n->getIdentifier());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();
                    QString Idreal = q1.value(1).toString();
                    QString Text = q1.value(2).toString();
                    qDebug() << Id <<"Idreal"<<Idreal <<"Text:"<<Text  ;
                }
        }
        q1.finish();
        break;
    case 1://Image
        Image* nouveau_i;
        nouveau_i=static_cast<Image*>(n);
        q1.prepare("SELECT * FROM Image WHERE Idreal=:Id");
        q1.bindValue(":Id",n->getIdentifier());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();

                    qDebug() << Id ;
                }
        }
        q1.finish();
        break;
    case 2://Task
        Task* nouveau_t;
        nouveau_t=static_cast<Task*>(n);
        q1.prepare("SELECT * FROM Task WHERE Idreal=:Id");
        q1.bindValue(":Id",n->getIdentifier());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();

                    qDebug() << Id ;
                }
        }
        q1.finish();


        break;
    case 3://Sound
        Sound* nouveau_s;
        nouveau_s=static_cast<Sound*>(n);
        q1.prepare("SELECT * FROM Sound WHERE Idreal=:Id");
        q1.bindValue(":Id",n->getIdentifier());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();
                    QString Idreal = q1.value(1).toString();
                    QString Text = q1.value(2).toString();
                    qDebug() << Id <<"Idreal"<<Idreal <<"Text:"<<Text  ;
                }
        }
        q1.finish();

        break;
    case 4://Video
        Video* nouveau_v;
        nouveau_v=static_cast<Video*>(n);
        q1.prepare("SELECT * FROM Video WHERE Idreal=:Id");
        q1.bindValue(":Id",n->getIdentifier());
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();
                    QString Idreal = q1.value(1).toString();
                    QString Text = q1.value(2).toString();
                    qDebug() << Id <<"Idreal"<<Idreal <<"Text:"<<Text  ;
                }
        }
        q1.finish();

        break;
    }

}

void version::select(Note* n, int i){
    /*verifier le type de n*/
    size_t nombre=strlen(typeid(*n).name());
    int num=10;
    std::string nom=std::string(typeid(*n).name(),nombre);
    std::string nom1="class Article",nom2="class Image",nom3="class Task",nom4="class Sound",nom5="class Video";
    QString genre;
    if(!nom.compare(nom1)){num=0;genre="Article";}
    if(!nom.compare(nom2)){num=1;genre="Image";}
    if(!nom.compare(nom3)){num=2;genre="Task";}
    if(!nom.compare(nom4)){num=3;genre="Sound";}
    if(!nom.compare(nom5)){num=4;genre="Video";}


    QSqlQuery q1;
    switch (num) {
    case 0://Article
        Article* nouveau_a;
        nouveau_a=static_cast<Article*>(n);
        q1.prepare("SELECT * FROM Article WHERE Id=:Id");
        q1.bindValue(":Id",i);
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();
                    QString Idreal = q1.value(1).toString();
                    qDebug() << Id <<" idreal: " <<Idreal ;
                }
        }
        q1.finish();
        break;
    case 1://Image
        Image* nouveau_i;
        nouveau_i=static_cast<Image*>(n);
        q1.prepare("SELECT * FROM Image WHERE Id=:Id");
        q1.bindValue(":Id",i);
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();

                    qDebug() << Id ;
                }
        }
        q1.finish();
        break;
    case 2://Task
        Task* nouveau_t;
        nouveau_t=static_cast<Task*>(n);
        q1.prepare("SELECT * FROM Task WHERE Id=:Id");
        q1.bindValue(":Id",i);
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();

                    qDebug() << Id ;
                }
        }
        q1.finish();
        break;
    case 3:
        Sound* nouveau_s;
        nouveau_s=static_cast<Sound*>(n);
        q1.prepare("SELECT * FROM Sound WHERE Id=:Id");
        q1.bindValue(":Id",i);
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();

                    qDebug() << Id ;
                }
        }
        q1.finish();

        break;
    case 4:
        Video* nouveau_v;
        nouveau_v=static_cast<Video*>(n);
        q1.prepare("SELECT * FROM Video WHERE Id=:Id");
        q1.bindValue(":Id",i);
        if (!q1.exec()) {
              QMessageBox::critical(0, QObject::tr("Database Error"),
                                    q1.lastError().text());
        }else{
            while (q1.next()) {
                    QString Id = q1.value(0).toString();

                    qDebug() << Id ;
                }
        }
        q1.finish();

        break;
    }

}
