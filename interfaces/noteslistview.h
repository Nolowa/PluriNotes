#ifndef NOTESLISTVIEW_H
#define NOTESLISTVIEW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QPushButton>
#include <QListView>
#include "notesmanager.h"
#include "utils.h"
#include <QMap>
#include <QModelIndex>
#include <QUuid>
#include <QHBoxLayout>
#include <QVBoxLayout>

class NotesListView : public QWidget
{
    Q_OBJECT

    NotesManager& nm;

    QVBoxLayout* layout;
    QListView* listview;

    QHBoxLayout* btnsLayout;
    QPushButton** buttons;

    void initUI();

    QModelIndex* findIndex(const Note&) const;
    QStandardItem* generateItem(const Note&);
    QStandardItem* updateItem(QStandardItem*, const Note&);

public:
    explicit NotesListView(NotesManager& nm, QWidget *parent = 0);


signals:
    void noteSelected(const Note *);
public slots:
    void selectionChanged(QItemSelection, QItemSelection);
};

#endif // NOTESLISTVIEW_H
