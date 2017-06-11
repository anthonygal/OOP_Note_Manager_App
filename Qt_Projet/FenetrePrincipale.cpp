#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(Manager& m, QWidget *parent) : QMainWindow(parent), manager(m){
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

    QDockWidget *leftDockWidget = new QDockWidget("Toutes les notes");
        leftDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        QWidget *leftWidget = new QWidget;
        QVBoxLayout *leftLayout = new QVBoxLayout;
            QVBoxLayout *partieNotesActives = new QVBoxLayout;
                for(Manager::IteratorNotes it=m.getIteratorNotes();!it.isDone();it.next()){
                    if(it.current().getEtat() == active){
                        QNoteReduite *qnr = new QNoteReduite(it.current(),this);
                        partieNotesActives->addWidget(qnr);
                    }
                }
            leftLayout->addLayout(partieNotesActives);
            QVBoxLayout *partieNotesArchivees = new QVBoxLayout;
            for(Manager::IteratorNotes it=m.getIteratorNotes();!it.isDone();it.next()){
                if(it.current().getEtat() == archivee){
                    QNoteReduite *qnr = new QNoteReduite(it.current(),this);
                    partieNotesArchivees->addWidget(qnr);
                }
            }
            leftLayout->addLayout(partieNotesArchivees);
        leftWidget->setLayout(leftLayout);
        leftDockWidget->setWidget(leftWidget);
    addDockWidget(Qt::LeftDockWidgetArea,leftDockWidget);

    Manager::IteratorNotes it = m.getIteratorNotes();
    while(it.current().getEtat() != active) it.next();
    QNote *qn = new QNote(it.current(),this);
    setCentralWidget(qn);
}
