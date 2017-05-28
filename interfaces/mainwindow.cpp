#include "mainwindow.h"

MainWindow::MainWindow(NotesManager& nm, RelationsManager<Note>& rm, QWidget *parent) : QMainWindow(parent)
{

    mf = new Mainframe(nm);
    setCentralWidget(mf);

    relationsView = new RelatedDockView(rm);
    relationsDock = new QDockWidget("Relations", this);
    relationsDock->setAllowedAreas(Qt::RightDockWidgetArea);
    relationsDock->setWidget(relationsView);
    relationsDock->setFeatures(QDockWidget::DockWidgetClosable);

    connect(mf->getListView(), SIGNAL(noteSelected(const Note*)), relationsView, SLOT(setSelectedNote(const Note*)));

    addDockWidget(Qt::RightDockWidgetArea, relationsDock);
    setWindowTitle("PluriNotes");
    setWindowIcon(QIcon(":/icons/article"));
}
