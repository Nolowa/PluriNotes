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


    QComboBox * versions;
    QPushButton* choisir;
    int Id;
    std::vector <int> a;
public:
    TaskInterface(const Task& t, QWidget *parent = 0);
    void parcourir();
public slots:
    void save();
    void charger();
    void enregistrerid(int i);
};

#endif // TASKINTERFACE_H


