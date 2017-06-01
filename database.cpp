#include "database.h"
#include "notes/article.h"
#include "notes/image.h"
#include "notes/sound.h"
#include "notes/video.h"
#include "notes/task.h"

Database::Database(NotesManager& nm, const QString& filename) : notesManager(nm), filename(filename){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    open = db.open();

    if(!open) throw new AppException("Impossible de se connecter à la base de données. La sauvegarde des données ne sera pas disponible.");

    createTables();
    //if(!createTables()) throw new AppException("Erreur lors de l'initialisation de la base de données.");

    types << "Article" << "Image" << "Task" << "Sound" << "Video";

   QObject::connect(&nm, SIGNAL(noteCreated(NoteHolder)), this, SLOT(insertVersion(NoteHolder)));
   QObject::connect(&nm, SIGNAL(noteUpdated(NoteHolder)), this, SLOT(insertVersion(NoteHolder)));
   QObject::connect(&nm, SIGNAL(noteStatusChanged(NoteHolder)), this, SLOT(updateStatus(NoteHolder)));

}

bool Database::createTables(){
        QSqlQuery query;
        bool result =
           query.exec("CREATE TABLE IF NOT EXISTS Note (Id INTEGER PRIMARY KEY AUTOINCREMENT,Genre VARCHAR(20) NOT NULL, HolderId VARCHAR NOT NULL, Title VARCHAR(20) ,Created TEXT, Edited TEXT,State INT);")
        && query.exec("CREATE TABLE IF NOT EXISTS Article (Id INTEGER NOT NULL,Text TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id) ON DELETE CASCADE);")
        && query.exec("CREATE TABLE IF NOT EXISTS Image (Id INTEGER NOT NULL,Description TEXT ,File TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);")
        && query.exec("CREATE TABLE IF NOT EXISTS Task (Id INTEGER NOT NULL,ActionToBeDone TEXT ,Status VARCHAR(20) ,Priority INT(1) , Expired TEXT , PRIMARY KEY (Id), FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);")
        && query.exec("CREATE TABLE IF NOT EXISTS Sound (Id INTEGER NOT NULL,Description TEXT ,File TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);")
        && query.exec("CREATE TABLE IF NOT EXISTS Video (Id INTEGER NOT NULL,Description TEXT ,File TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);");

        return result;
}

void Database::insertVersion(const NoteHolder& note){
    if(ignoreManagerSignal) return;

    const Note& content = note.getLastVersion();
    const QString& type = content.getType();
    const QString& uuid = note.getId().toString();

    // Insertion des données de la version de la note
    QSqlQuery q;
    q.prepare("INSERT INTO Note(HolderId,Genre,Title,Created,Edited,State) VALUES (:HolderId, :Genre,:Title,:Created,:Edited,:State)");
    q.bindValue(":HolderId",uuid);
    q.bindValue(":Genre",type);
    q.bindValue(":Title",content.getTitle());
    q.bindValue(":Created",note.getCreated());
    q.bindValue(":Edited",content.getEdited());
    q.bindValue(":State",note.getState());

    if(!q.exec()) throw new AppException("Erreur lors de l'insertion d'une note en base de donnée");

    // Id de la version en base de donnée
    int id= q.lastInsertId().toInt();
    q.finish();

    q = QSqlQuery();
    bool subtable = true;

    if(type == "Article"){ // Article
        const Article& content_a = static_cast<const Article&>(content);
        q.prepare("INSERT INTO Article(Id, Text) VALUES (:Id, :Text)");
        q.bindValue(":Text", content_a.getText());
    } else

    if(type == "Task"){
        const Task& content_t = static_cast<const Task&>(content);
        q.prepare("INSERT INTO Task(Id,ActionToBeDone,Status,Priority,Expired) VALUES (:Id,:ActionToBeDone,:Status,:Priority,:Expired)");
        q.bindValue(":Id",id);
        q.bindValue(":ActionToBeDone",content_t.getActionToBeDone());
        q.bindValue(":Status",content_t.getStatus_re());
        q.bindValue(":Priority",content_t.getPriority());
        q.bindValue(":Expired",content_t.getExpired());

    } else

    if(const NoTextualNote* content_n = &dynamic_cast<const NoTextualNote&>(content)){ // Image + Sound + Video
        q.prepare("INSERT INTO " + type + "(Id, Description, File) VALUES (:Id, :Description, :File)");
        q.bindValue(":Description", content_n->getDescription());
        q.bindValue(":File", content_n->getFilename());
    } else {
        subtable = false;
    }

    if(subtable){
        q.bindValue(":Id", id);
        if(!q.exec()) throw new AppException("Erreur lors de l'insertion d'une note en base de donnée");

        q.finish();
    }
}

void Database::updateStatus(const NoteHolder &n){
    if(ignoreManagerSignal) return;

    QSqlQuery q;
    q.exec("UPDATE Note SET Task = " + QString::number(n.getState())  +" WHERE HolderId = \"" + n.getId().toString() + "\"");
    qDebug() << q.lastError().text();
    //f(!q.exec()) throw new AppException("Erreur lors de la mise à jour d'une note en base de donnée");
}

const Note& Database::loadContent(int version_id, const QString& note_type){
    QSqlQuery q;
    q.exec("SELECT * FROM (Note INNER JOIN " + note_type + " T ON Note.Id = T.Id) WHERE Note.Id='"+ QString::number(version_id) +"';");
    q.next();

    Note& note = notesManager.createNoteBody(note_type);

    if(note_type == "Article"){
        Article& a = static_cast<Article&>(note);
        a.setText(q.value("Text").toString());
        note = a;
    } else

    if(note_type == "Task"){
        Task& a = static_cast<Task&>(note);
        a.setActionToBeDone(q.value("ActionToBeDone").toString());
        a.setStatus(q.value("Status").toInt());
        a.setPriority(q.value("Priority").toInt());
        a.setExpired(q.value("Expired").toDateTime());

    } else if(NoTextualNote* a = &dynamic_cast<NoTextualNote&>(note)){
        a->setDescription(q.value("Description").toString());
        a->setFilename(q.value("File").toString());
    }else{
        throw new AppException("Note de type inconnu");
    }

    note.setTitle(q.value("Title").toString());

    return note;
}

void Database::loadAll(){
    ignoreManagerSignal = true;

    QSqlQuery q("SELECT Id, HolderId, Max(Edited), Created, State, Genre FROM Note GROUP BY HolderId ORDER BY Created DESC");
    while(q.next()){
        const Note& content = loadContent(q.value("Id").toInt(), q.value("Genre").toString());
        notesManager.import(q.value("HolderId").toString(), q.value("Created").toDateTime(), q.value("State").toInt(), content);
    }
    ignoreManagerSignal = false;
}


Database::~Database(){
    if(open) db.close();
}

