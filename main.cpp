#include <QApplication>
#include <QtWidgets>
#include <QTextStream>
#include <QTimer>
#include <QTreeView>
#include "notesmanager.h"
#include "memento.h"
#include "database.h"
#include "interfaces/sidebar/sidebar.h"
#include "interfaces/mainwindow.h"
#include <QStandardItemModel>
#include <QMap>
#include <QModelIndex>
#include <QMessageBox>


//include de test


int main(int argc, char *argv[]){


            QApplication app(argc, argv);
    try{
            QTextStream qout(stdout);
            qout << "Demarrage" << endl;

            NotesManager& m=NotesManager::getInstance();
            RelationsManager<NoteHolder>* rm = new RelationsManager<NoteHolder>; // Penser à faire le DP singleton -> Non.
            MementoCaretaker* mainMemento= new MementoCaretaker; // Penser à faire le DP singleton

            rm->createRelation("UneRelationUnidirectionelle");
            rm->createRelation("UneDeuxiemeRelation");

            Database* db =new Database(m, "database.db");
            db->loadAll();

            MainWindow window(m, *rm);

            window.show();

            return app.exec();
    }catch(AppException* ex){
        QMessageBox::critical(nullptr, "Erreur", ex->message);

    }
}
