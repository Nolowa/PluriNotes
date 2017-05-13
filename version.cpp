#include "version.h"
QSqlDatabase version::db = QSqlDatabase::addDatabase("QSQLITE");
int version::table_exist=0;
int version::open=0;
bool version::connectBd(){
    db.setDatabaseName("lo21");
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
        bool result = query.exec("CREATE TABLE IF NOT EXISTS 'Note' ('Id' INT AUTO_INCREMENT NOT NULL,'Genre' VARCHAR(20) NOT NULL, 'Title' VARCHAR(20) ,'Created' TEXT, 'Edited' TEXT,'State' VARCHAR(20), PRIMARY KEY ('Id'));");
        if(result)
        {
            std::cout << "table Note crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table note" << std::endl << q2c(query.lastError().text()) << std::endl;
        }
        bool result1 = query.exec("CREATE TABLE IF NOT EXISTS 'Article' ('Id' int(10) NOT NULL,'Idreal' VARCHAR(20) NOT NULL,'Text' TEXT NOT NULL, PRIMARY KEY ('Id'));");
        if(result1)
        {
            std::cout << "table Article crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table Article" << std::endl << q2c(query.lastError().text()) << std::endl;
        }
        bool result2 = query.exec("CREATE TABLE IF NOT EXISTS 'Image' ('Id' int(10) NOT NULL,'Idreal' VARCHAR(20) NOT NULL,'Description' TEXT NOT NULL,'File' TEXT NOT NULL, PRIMARY KEY ('Id'));");
        if(result2)
        {
            std::cout << "table Image crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table Image" << std::endl << q2c(query.lastError().text()) << std::endl;
        }
        bool result3 = query.exec("CREATE TABLE IF NOT EXISTS 'Task' ('Id' int(10) NOT NULL,'Idreal' VARCHAR(20) NOT NULL,'ActionToBeDone' TEXT NOT NULL,'Status' VARCHAR(20) NOT NULL,'Priority' INT(1) NOT NULL,"
                                  "TEXT'Expired' TEXT NOT NULL, PRIMARY KEY ('Id'));");
        if(result3)
        {
            std::cout << "table Task crée" << std::endl;
        }
        else
        {
            std::cout << "Une erreur s'est produite. table Task" << std::endl << q2c(query.lastError().text()) << std::endl;
        }


}

