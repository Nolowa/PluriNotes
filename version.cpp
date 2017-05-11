#include "version.h"
int db=0;
/*version::version()
{

}
void version::connectBd(){
    int rc;
    rc = sqlite3_open("version.db", &db);//ouvrir une base de donné, si non existant créer une nouvelle

    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }
}

void version::createTables(){
    char *zErrMsg = 0;
    char sql[]="CREATE TABLE Note("  \
               "Id INT(5)  AUTO_INCREMENT  NOT NULL," \
               "Genre          TEXT    NOT NULL"
               "PRIMARY KEY (`id`));";
    char sql1[]="CREATE TABLE Article("  \
                "ID INT PRIMARY KEY     NOT NULL," \
                "Text         TEXT );" ;
    char sql2[]="CREATE TABLE Image("  \
                "ID INT PRIMARY KEY     NOT NULL," \
                "Fichier         TEXT );";
    char sql3[]="CREATE TABLE Video("  \
                "ID INT PRIMARY KEY     NOT NULL," \
                "Fichier         TEXT );";
    char sql4[]= "CREATE TABLE Sound("  \
                 "ID INT PRIMARY KEY     NOT NULL," \
                 "Fichier         TEXT );";
    char sql5[]="CREATE TABLE task("  \
                "ID INT PRIMARY KEY     NOT NULL," \
                "actionToBeDone         TEXT," \
                "Priority       INT CHECK(Priority<6 AND Priority>=0)," \
                "expired                TEXT);";
    int rc;
    /*Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, sql1, callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, sql3, callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, sql4, callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, sql5, callback, 0, &zErrMsg);

}*/
