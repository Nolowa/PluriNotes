#include "notesproxyfilter.h"

NotesProxyFilter::NotesProxyFilter(const NotesManager& manager, NoteState status, QObject *parent) : QSortFilterProxyModel(parent), manager(manager), status(static_cast<int>(status)){
    setSourceModel(&manager.getModelHolder().getModel());
    setDynamicSortFilter(true);

}

bool NotesProxyFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const{
    Q_UNUSED(sourceParent)
    const NoteHolder& note = manager.getModelHolder().findByIndex(sourceModel()->index(sourceRow, 0));
    return note.getState() == status;

}
