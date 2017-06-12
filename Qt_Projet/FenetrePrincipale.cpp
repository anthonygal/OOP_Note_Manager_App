#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent){
    Manager& manager = Manager::donneInstance();

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
            QScrollArea *scrollAreaActives = new QScrollArea;
                QWidget *notesActivesWidget = new QWidget;
                QVBoxLayout *notesActivesLayout = new QVBoxLayout;
                    for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next())
                        if(it.current().getEtat() == active)
                            notesActivesLayout->addWidget(new QNoteReduite(it.current(),this));
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
        while(!it.isDone() && it.current().getEtat() != active && !it.current().isActuelle())
            it.next();
        QNote *notePrincipale = new QNote(it.current());
    centralLayout->addWidget(notePrincipale);

        QScrollArea *anciennesVersions = new QScrollArea;
            QWidget *oldVerWidget = new QWidget;
            QVBoxLayout *oldVerLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it2=manager.getIteratorNotes();!it2.isDone();it2.next()){
                    if(it2.current().getID() == it.current().getID() && !it2.current().isActuelle()){
                        oldVerLayout->addWidget(new QNoteReduite(it2.current(),this));
                    }
                }
            oldVerWidget->setLayout(oldVerLayout);
        anciennesVersions->setWidget(oldVerWidget);
        anciennesVersions->setWidgetResizable(true);
    centralLayout->addWidget(anciennesVersions);

    zoneCentrale->setLayout(centralLayout);
    setCentralWidget(zoneCentrale);


    QDockWidget *rightDockWidget = new QDockWidget("Relations de la note principale");
        QWidget *rightWidget = new QWidget;
        QVBoxLayout *rightLayout = new QVBoxLayout;
            QScrollArea *scrollRelAsc = new QScrollArea;
                QWidget *relAscWidget = new QWidget;
                QVBoxLayout *relAscLayout = new QVBoxLayout;
                    for(Manager::IteratorRelations it=manager.getIteratorRelations();!it.isDone();it.next()){
                        //A faire
                    }
                relAscWidget->setLayout(relAscLayout);
            scrollRelAsc->setWidget(relAscWidget);
            scrollRelAsc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelAsc);

            QScrollArea *scrollRelDesc = new QScrollArea;
                QWidget *relDescWidget = new QWidget;
                QVBoxLayout *relDescLayout = new QVBoxLayout;
                    for(Manager::IteratorRelations it=manager.getIteratorRelations();!it.isDone();it.next()){
                        //A faire
                    }
                relDescWidget->setLayout(relDescLayout);
            scrollRelDesc->setWidget(relDescWidget);
            scrollRelDesc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelDesc);
    rightDockWidget->setWidget(rightWidget);
    addDockWidget(Qt::RightDockWidgetArea,rightDockWidget);
}

void FenetrePrincipale::updateCentralWidget(Note& n){
    QWidget *zoneCentrale = new QWidget;
    QVBoxLayout *centralLayout = new QVBoxLayout;

        QNote *notePrincipale = new QNote(n);
    centralLayout->addWidget(notePrincipale);

        QScrollArea *anciennesVersions = new QScrollArea;
            QWidget *oldVerWidget = new QWidget;
            QVBoxLayout *oldVerLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it=Manager::donneInstance().getIteratorNotes();!it.isDone();it.next()){
                    if(it.current().getID() == n.getID() && !it.current().isActuelle()){
                        oldVerLayout->addWidget(new QNoteReduite(it.current(),this));
                    }
                }
            oldVerWidget->setLayout(oldVerLayout);
        anciennesVersions->setWidget(oldVerWidget);
        anciennesVersions->setWidgetResizable(true);
    centralLayout->addWidget(anciennesVersions);

    zoneCentrale->setLayout(centralLayout);
    setCentralWidget(zoneCentrale);
}

//void updateRightDockWidget(Note& n){
//    QDockWidget *rightDockWidget = new QDockWidget("Relations de la note principale");
//        QWidget *rightWidget = new QWidget;
//        QVBoxLayout *rightLayout = new QVBoxLayout;
//            QScrollArea *scrollRelAsc = new QScrollArea;
//                QWidget *relAscWidget = new QWidget;
//                QVBoxLayout *relAscLayout = new QVBoxLayout;
//                    for(Manager::IteratorRelations it=manager.getIteratorRelations();!it.isDone();it.next()){
//                        //A faire
//                    }
//                relAscWidget->setLayout(relAscLayout);
//            scrollRelAsc->setWidget(relAscWidget);
//            scrollRelAsc->setWidgetResizable(true);
//        rightLayout->addWidget(scrollRelAsc);

//            QScrollArea *scrollRelDesc = new QScrollArea;
//                QWidget *relDescWidget = new QWidget;
//                QVBoxLayout *relDescLayout = new QVBoxLayout;
//                    for(Manager::IteratorRelations it=manager.getIteratorRelations();!it.isDone();it.next()){
//                        //A faire
//                    }
//                relDescWidget->setLayout(relDescLayout);
//            scrollRelDesc->setWidget(relDescWidget);
//            scrollRelDesc->setWidgetResizable(true);
//        rightLayout->addWidget(scrollRelDesc);
//    rightDockWidget->setWidget(rightWidget);
//    addDockWidget(Qt::RightDockWidgetArea,rightDockWidget);
//}

void FenetrePrincipale::changerNotePrincipale(Note &n){
    updateCentralWidget(n);
}
