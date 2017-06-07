#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent){
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
    QLabel *labID = new QLabel("ID : ",this);
    QLabel *ID = new QLabel(QString::number(n.getID()),this);
    QLabel *labTitre = new QLabel("Titre : ",this);
    QLabel *Titre = new QLabel(n.getTitre(),this);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
        hlayout1->addWidget(labID);
        hlayout1->addWidget(ID);
    QHBoxLayout *hlayout2 = new QHBoxLayout;
        hlayout2->addWidget(labTitre);
        hlayout2->addWidget(Titre);
    QVBoxLayout *vlayout = new QVBoxLayout;
        vlayout->addLayout(hlayout1);
        vlayout->addLayout(hlayout2);
    zoneCentrale->setLayout(vlayout);
    setCentralWidget(zoneCentrale);
}
