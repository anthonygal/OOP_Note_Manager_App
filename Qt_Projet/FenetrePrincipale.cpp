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


    leftDockWidget = new QDockWidget("Toutes les notes");
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
        notePrincipale = new QNote(it.current());
    centralLayout->addWidget(notePrincipale);

        autresVersions = new QScrollArea;
            QWidget *autresVerWidget = new QWidget;
            QVBoxLayout *autresVerLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it2=manager.getIteratorNotes();!it2.isDone();it2.next()){
                    if(it2.current().getID() == notePrincipale->getNote().getID() && it2.current().getDateModif() != notePrincipale->getNote().getDateModif()){
                        QHBoxLayout *hlayout = new QHBoxLayout;
                            hlayout->addWidget(new QLabel(it2.current().getDateModif().toString(formatDateTime)));
                            hlayout->addWidget(new QNoteReduite(it2.current(),this));
                        autresVerLayout->addLayout(hlayout);
                    }
                }
            autresVerWidget->setLayout(autresVerLayout);
        autresVersions->setWidget(autresVerWidget);
        autresVersions->setWidgetResizable(true);
    centralLayout->addWidget(autresVersions);

    zoneCentrale->setLayout(centralLayout);
    setCentralWidget(zoneCentrale);


    rightDockWidget = new QDockWidget("Relations de la note principale");
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

void FenetrePrincipale::updateNotePrincipale(Note& n){
    QNote *oldNotePrincipale = notePrincipale;
    QNote *newNotePrincipale = new QNote(n);
    centralWidget()->layout()->replaceWidget(notePrincipale, newNotePrincipale);
    notePrincipale = newNotePrincipale;
    delete oldNotePrincipale;
}

void FenetrePrincipale::updateAutresVersions(Note& n){
    QScrollArea *oldAutreVersions = autresVersions;

    QScrollArea *newAutresVersions = new QScrollArea;
        QWidget *autresVerWidget = new QWidget;
        QVBoxLayout *autresVerLayout = new QVBoxLayout;
            for(Manager::IteratorNotes it=Manager::donneInstance().getIteratorNotes();!it.isDone();it.next()){
                if(it.current().getID() == n.getID() && it.current().getDateModif() != n.getDateModif()){
                    QHBoxLayout *hlayout = new QHBoxLayout;
                        hlayout->addWidget(new QLabel(it.current().getDateModif().toString(formatDateTime)));
                        hlayout->addWidget(new QNoteReduite(it.current(),this));
                    autresVerLayout->addLayout(hlayout);
                }
            }
        autresVerWidget->setLayout(autresVerLayout);
    newAutresVersions->setWidget(autresVerWidget);
    newAutresVersions->setWidgetResizable(true);

    centralWidget()->layout()->replaceWidget(autresVersions, newAutresVersions);
    autresVersions = newAutresVersions;
    delete oldAutreVersions;
}

void FenetrePrincipale::updateRightDockWidget(Note& n){
    Manager& manager = Manager::donneInstance();

    QWidget *oldDockWidget = rightDockWidget->widget();

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
    //rightWidget->show(); //surement besoin
    delete oldDockWidget;
}

void FenetrePrincipale::changerNotePrincipale(Note &n){
    updateNotePrincipale(n);
    updateAutresVersions(n);
    updateRightDockWidget(n);
}
