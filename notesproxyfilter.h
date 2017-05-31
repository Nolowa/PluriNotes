#ifndef NOTESPROXYFILTER_H
#define NOTESPROXYFILTER_H

#include "notes/noteholder.h"
#include "notesmanager.h"
#include <QSortFilterProxyModel>


class NotesProxyFilter : public QSortFilterProxyModel
{

    const NotesManager& manager;
    int status;
    Q_OBJECT

public:
    explicit NotesProxyFilter(const NotesManager& manager, NoteState status, QObject *parent = 0);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;



signals:

public slots:
};

#endif // NOTESPROXYFILTER_H
