#ifndef CORBEILLELISTVIEW_H
#define CORBEILLELISTVIEW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QPushButton>
#include <QListView>
#include "corbeille.h"
#include "utils.h"
#include <QMap>
#include <QModelIndex>
#include <QFrame>
#include <QUuid>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "iostream"

class CorbeilleListView: public QWidget
{
    Q_OBJECT

    Corbeille& cb;
    QStandardItemModel model;
    QMap<QUuid, QModelIndex> indexMap;

    QVBoxLayout* layout;
    QListView* listview;

    QHBoxLayout* btnsLayout;
    QPushButton** buttons;

    void generateModel();
    void initUI();

    QModelIndex* findIndex(const Note&) const;
    QStandardItem* generateItem(const Note&);
    QStandardItem* updateItem(QStandardItem*, const Note&);
public:
    explicit CorbeilleListView(Corbeille& cob, QWidget *parent = 0);


signals:
    void noteSelected(const Note *);
    void supprimer(const Note*);
public slots:
    void noteAdded(const Note&);
    void noteUpdated(const Note&);
    void selectionChanged(QItemSelection, QItemSelection);
};

#endif // CORBEILLELISTVIEW_H
