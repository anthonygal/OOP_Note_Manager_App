#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(Manager& m, QWidget *parent) : QMainWindow(parent), manager(m){
    QAction* actionQuitter = new QAction("&Quitter", this);
    QAction* newArticle = new QAction("Article", this);
    QAction* newTache = new QAction("Tache", this);
    QAction* newMultimedia = new QAction("Article", this);

    QMenu* menuAfficher = menuBar()->addMenu("&Fichier");
        menuAfficher->addAction(actionQuitter);
    QMenu* menuNotes = menuBar()->addMenu("&Notes");
        QMenu* newNote = menuNotes->addMenu("Nouvelle note");
            newNote->addAction(newArticle);
            newNote->addAction(newTache);
            newNote->addAction(newMultimedia);

    Manager::IteratorNotes it = m.getIteratorNotes();
//    it.next();
//    it.next();
    Note& n = it.current();
    QNote qn(n,this);
    //QLabel* zoneCentrale = new QLabel("Aucune note n'a ete selectionnée");
    QWidget* zoneCentrale = new QWidget();
    zoneCentrale->setLayout(qn.layout());
    setCentralWidget(zoneCentrale);
}
