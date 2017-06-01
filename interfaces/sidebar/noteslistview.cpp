#include "noteslistview.h"

NotesListView::NotesListView(const NotesManager& manager, NoteState state, QWidget *parent) : QListView(parent), manager(manager)
{
    filter = new NotesProxyFilter(manager, state, this);
    setModel(filter);
    setStyleSheet("background: #fcfcfc; border:0;");
    clearSelection();

    if(state == ACTIVE)
        setIconSize(QSize(32, 32));

}

void NotesListView::selectionChanged(const QItemSelection& cur, const QItemSelection& prev){
    Q_UNUSED(prev);

    if(cur.size()){
        emit noteSelected(&manager.getModelHolder().findByIndex(filter->mapSelectionToSource(cur).indexes().first()));
    }
}
