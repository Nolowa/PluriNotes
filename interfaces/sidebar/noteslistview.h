#ifndef NOTESLISTVIEW_H
#define NOTESLISTVIEW_H

#include <QWidget>
#include <QListView>
#include "notesmanager.h"
#include "notes/noteholder.h"
#include "notesproxyfilter.h"

class NotesListView : public QListView
{
    NotesProxyFilter* filter;
    const NotesManager& manager;

    Q_OBJECT
public:
    explicit NotesListView(const NotesManager& manager, NoteState state, QWidget *parent = 0);

signals:
    void noteSelected(const NoteHolder*);
public slots:
    void selectionChanged(const QItemSelection&, const QItemSelection&);
};

#endif // NOTESLISTVIEW_H
