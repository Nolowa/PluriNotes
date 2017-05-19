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

#include "generalinterface.h"
#include "notes/task.h" // inclusion récursif.?
class Task;
class GeneralInterface;

class TaskInterface: public GeneralInterface {
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
public:
    TaskInterface(const Task& t, QWidget *parent = 0);
public slots:
    void save();
};

#endif // TASKINTERFACE_H


