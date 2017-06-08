#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent){
    const QString format2 = "dd/mm/yyyy hh:mm:ss";

    QMenu *menuAfficher = menuBar()->addMenu("&Fichier");
        QAction *actionQuitter = new QAction("&Quitter", this);
        menuAfficher->addAction(actionQuitter);
    QMenu *menuNotes = menuBar()->addMenu("&Notes");
        QMenu *newNote = menuNotes->addMenu("Nouvelle note");
            QAction *newArticle = new QAction("Article", this);
            QAction *newTache = new QAction("Tache", this);
            QAction *newMultimedia = new QAction("Article", this);
            newNote->addAction(newArticle);
            newNote->addAction(newTache);
            newNote->addAction(newMultimedia);

    Manager& m = Manager::donneInstance();
    const Note& n = m.getConstIteratorNotes().current();

    QWidget *zoneCentrale = new QWidget;
    QVBoxLayout *layout = n.afficher(this);
    QHBoxLayout *layouth = new QHBoxLayout;
    QLabel *ldtry = new QLabel("Essai Date : ");
    layouth->addWidget(ldtry);
    QDateTime date = QDateTime::fromString("11/12/2016 07:43:37",format2);
    if(!date.isValid()){ QLabel *error = new QLabel("Erreur !!!"); layouth->addWidget(error);}
    QLabel *dtry = new QLabel(date.toString(format2));
    layouth->addWidget(dtry);
    layout->addLayout(layouth);
    zoneCentrale->setLayout(layout);
    setCentralWidget(zoneCentrale);
}
