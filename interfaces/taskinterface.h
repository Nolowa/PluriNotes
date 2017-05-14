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
#include "notes/task.h" // inclusion récursif.?
class Task;

class TaskInterface: public QWidget{
    Q_OBJECT
    Task* task;
    QLineEdit* titleEdit;
    QTextEdit* actionEdit;
    QLineEdit* dateEdit;
    QComboBox* statusCombo;
    QComboBox* priorityCombo;
    QFormLayout* layout;
    QPushButton* generate;
public:
    TaskInterface(Task* t,QWidget *parent = 0);
public slots:
    void save();
};

#endif // TASKINTERFACE_H


