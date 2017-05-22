#include "mainwindow.h"

MainWindow::MainWindow(NotesManager& nm, QWidget *parent) : QMainWindow(parent)
{

    mf = new Mainframe(nm);
    setCentralWidget(mf);
    setWindowTitle("PluriNotes");
    setWindowIcon(QIcon(":/icons/article"));
}
