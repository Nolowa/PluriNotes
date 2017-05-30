#ifndef TASKINTERFACE_H
#define TASKINTERFACE_H

#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <QVector>

#include "noteinterface.h"
#include "notes/task.h" // inclusion récursif.?
class Task;
class GeneralInterface;

class TaskInterface: public NoteInterface {
    Q_OBJECT
    const Task* task;
    QLineEdit* titleEdit;
    QTextEdit* actionEdit;
    QLineEdit* idEdit;
    QLineEdit* dateEdit;
    QComboBox* statusCombo;
    QComboBox* priorityCombo;
    QFormLayout* layout;
    QPushButton* generate;

    /**< la partie choisir et charger les versions */
    QComboBox * versions;
    QPushButton* choisir;
    int Id;
    std::vector <int> a;

    QPushButton* activer;/**< archive->active */
    QLineEdit* priorityEdit;
    QLineEdit* statusEdit;
    QPushButton* supprimer;/**< supprimer */
public:
    TaskInterface(const Task& t, QWidget *parent = 0);
    void parcourir();/**< parcourir les versions*/
public slots:
    void save();
    void charger();/**< charger la version*/
    void enregistrerid(int i);/**< garder id présent*/
};

#endif // TASKINTERFACE_H


