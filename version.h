#ifndef VERSION_H
#define VERSION_H
#include "notesmanager.h"
#include "sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

class version
{
    static int db;
public:
    version();
    static void connectBd();
    //static void closeBd(){sqlite3_close(db);}
};

void createTables();


#endif // VERSION_H
