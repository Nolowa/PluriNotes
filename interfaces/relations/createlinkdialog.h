#ifndef CREATELINKDIALOG_H
#define CREATELINKDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>
#include "notes/note.h"
#include "relations/relationsmanager.h"
#include "relations/relationship.h"
#include "notesmanager.h"

class CreateLinkDialog : public QDialog
{
    NotesManager& notesManager = NotesManager::getInstance();
    RelationsManager<NoteHolder>& relationsManager;
    QVBoxLayout* glblLayout;
    QFormLayout* formLayout;
    QComboBox* relationCombo;
    QComboBox* relatedCombo;
    QLineEdit* labelField;
    QDialogButtonBox* btnsLayout;

    const NoteHolder* currentNote;

    void initUI();
    void populate();
    void accept();


    Q_OBJECT
public:
    explicit CreateLinkDialog(RelationsManager<NoteHolder>& relationsManager, QWidget *parent = 0);
    void setCurrentNote(const NoteHolder& n);

signals:

public slots:
};

#endif // CREATELINKDIALOG_H
