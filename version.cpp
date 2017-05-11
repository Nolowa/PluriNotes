#include "version.h"
/*
version::version()
{

}
version::connectBd(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("version.db", &db);//ouvrir une base de donné, si non existant créer une nouvelle

    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }
}

void createTables(){
     char *sql;
     sql = "CREATE TABLE COMPANY("  \
             "ID INT PRIMARY KEY     NOT NULL," \
             "NAME           TEXT    NOT NULL," \
             "AGE            INT     NOT NULL," \
             "ADDRESS        CHAR(50)," \
             "SALARY         REAL );";

       // Execute SQL statement
     //  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
}
*/
