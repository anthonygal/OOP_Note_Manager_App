#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent), manager(Manager::donneInstance()){

    QMenu *menuAfficher = menuBar()->addMenu("&Fichier");
        QAction *actionQuitter = new QAction("&Quitter");
        menuAfficher->addAction(actionQuitter);
    QMenu *menuNotes = menuBar()->addMenu("&Notes");
        QMenu *newNote = menuNotes->addMenu("Nouvelle note");
            QAction *newArticle = new QAction("Article");
            QAction *newTache = new QAction("Tache");
            QAction *newMultimedia = new QAction("Article");
            newNote->addAction(newArticle);
            newNote->addAction(newTache);
            newNote->addAction(newMultimedia);

    QDockWidget *leftDockWidget = new QDockWidget("Toutes les notes");
    leftDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    QWidget *leftWidget = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout;
        QScrollArea *scrollAreaActives = new QScrollArea(leftWidget);
        QWidget *notesActivesWidget = new QWidget;
        QVBoxLayout *notesActivesLayout = new QVBoxLayout;
            for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next())
                if(it.current().getEtat() == active)
                    notesActivesLayout->addWidget(new QNoteReduite(it.current(),this,notesActivesWidget));
        notesActivesWidget->setLayout(notesActivesLayout);
        scrollAreaActives->setWidget(notesActivesWidget);
        scrollAreaActives->setWidgetResizable(true);
        leftLayout->addWidget(scrollAreaActives);

        QScrollArea *scrollAreaArchivees = new QScrollArea(leftWidget);
        QWidget *notesArchiveesWidget = new QWidget;
        QVBoxLayout *notesArchiveesLayout = new QVBoxLayout;
        for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next())
            if(it.current().getEtat() == archivee)
                notesArchiveesLayout->addWidget(new QNoteReduite(it.current(),this));
        notesArchiveesWidget->setLayout(notesArchiveesLayout);
        scrollAreaArchivees->setWidget(notesArchiveesWidget);
        scrollAreaArchivees->setWidgetResizable(true);
        leftLayout->addWidget(scrollAreaArchivees);
    leftWidget->setLayout(leftLayout);
    leftDockWidget->setWidget(leftWidget);
    addDockWidget(Qt::LeftDockWidgetArea,leftDockWidget);

    QWidget *zoneCentrale = new QWidget;
        QVBoxLayout *centralLayout = new QVBoxLayout;
            Manager::IteratorNotes it=manager.getIteratorNotes();
            while(!it.isDone() && it.current().getEtat() != active && !it.current().isActuelle()) it.next();
            notePrincipale = new QNote(it.current());
        centralLayout->addWidget(notePrincipale);

//            QVBoxLayout *oldVerLay = new QVBoxLayout;
//                for(Manager::IteratorNotes it2=manager.getIteratorNotes();!it2.isDone();it2.next()){
//                    if(it2.current().getID() == it.current().getID() && !it2.current().isActuelle()){
//                        QNoteReduite *qnr = new QNoteReduite(it2.current(),this);
//                        oldVerLay->addWidget(qnr);
//                    }
//                }
//            anciennesVersions->setLayout(oldVerLay);
//        centralLayout->addWidget(anciennesVersions);
    zoneCentrale->setLayout(centralLayout);
    setCentralWidget(zoneCentrale);
}

void FenetrePrincipale::updateCentralWidget(Note& n){
    QNote *newNotePrincipale = new QNote(n);
    setCentralWidget(newNotePrincipale);

//    QVBoxLayout *oldVerLay = new QVBoxLayout;
//        for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next()){
//            if(it.current().getID() == n.getID() && !it.current().isActuelle()){
//                QNoteReduite *qnr = new QNoteReduite(it.current(),this);
//                oldVerLay->addWidget(qnr);
//            }
//        }
//    anciennesVersions->setLayout(oldVerLay);
}

void FenetrePrincipale::changerNotePrincipale(Note &n){
    updateCentralWidget(n);
}
