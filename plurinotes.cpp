#include "plurinotes.h"

PluriNotes::PluriNotes(NotesManager& n): notesManager(&n){

    QMdiArea *zoneCentral= new QMdiArea;

    //Menu Bar
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QMenu *menuEdition = menuBar()->addMenu("&Edition");
    QMenu *fichiersRecents = menuFichier->addMenu("Fichiers &récents");
    menuEdition->addAction("Affichage");
    fichiersRecents->addAction("Fichier bidon 1.txt");
    fichiersRecents->addAction("Fichier bidon 2.txt");
    fichiersRecents->addAction("Fichier bidon 3.txt");

    QAction *actionQuitter = new QAction("&Quitter", this);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    fichiersRecents->addAction(actionQuitter);

    //Barre d'outils = Toolbars
    QToolBar *toolBarFichier = addToolBar("Fichier");
    toolBarFichier->addAction(actionQuitter);
    toolBarFichier->addSeparator();
    QFontComboBox *choixPolice = new QFontComboBox;
    toolBarFichier->addWidget(choixPolice);

    //Central Widget
    QLineEdit *nom= new QLineEdit;
    QLineEdit *prenom= new QLineEdit;
    QLineEdit *age= new QLineEdit;
    QFormLayout *layoutPrincipal= new QFormLayout;
    layoutPrincipal->addRow("Nom",nom);
    layoutPrincipal->addRow("Prénom",prenom);
    layoutPrincipal->addRow("Age",age);
    zoneCentral-> setLayout(layoutPrincipal);
    setCentralWidget(zoneCentral);

    QTextEdit *zoneTexte1 = new QTextEdit;

    QMdiSubWindow *sousFenetre1 = zoneCentral->addSubWindow(zoneTexte1);

    setCentralWidget(zoneCentral);

}
