#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent){
    Manager& manager = Manager::donneInstance();

    //MENU
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

    //DOCK WIDGET GAUCHE
    leftDockWidget = new QDockWidget("Toutes les notes");

    leftDockWidget->setStyleSheet("background-color: white");
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

    //ZONE CENTRALE
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

    //DOCK WIDGET DROIT
    rightDockWidget = new QDockWidget("Relations de la note principale");
        QWidget *rightWidget = new QWidget;
        QVBoxLayout *rightLayout = new QVBoxLayout;

            QLabel *labRelAsc = new QLabel("Relations Ascendantes : ");
        rightLayout->addWidget(labRelAsc);

            scrollRelAsc = new QScrollArea;
                QWidget *relAscWidget = new QWidget;
                QVBoxLayout *relAscLayout = new QVBoxLayout;
                //Affiche les references ascendantes
                //Donc l' ID de la note principale doit correspondre à l'id2 des couples
                relAscLayout->addWidget(new QLabel(manager.getReference().getTitre()));
                for(Relation::IteratorCouples itc=manager.getReference().getIteratorCouples();!itc.isDone();itc.next()){
                    if(notePrincipale->getID() == itc.current().getID2()){
                        QHBoxLayout *coupleLayout = new QHBoxLayout;
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1())),this));
                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2())),this));
                        relAscLayout->addLayout(coupleLayout);
                    }
                }
                //Affiche les relations ascendantes
                //Donc l' ID de la note principale doit correspondre à l'id2 des couples des relations orientees et à l'un des deux id des couples des relations non orientees
                    for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next()){
                        relAscLayout->addWidget(new QLabel(itr.current().getTitre()));
                        for(Relation::IteratorCouples itc=itr.current().getIteratorCouples();!itc.isDone();itc.next()){
                            if((itr.current().isOrientee() && notePrincipale->getID() == itc.current().getID2()) || (!itr.current().isOrientee() && (notePrincipale->getID() == itc.current().getID1() || notePrincipale->getID() == itc.current().getID2()))){
                                QHBoxLayout *coupleLayout = new QHBoxLayout;
                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1())),this));
                                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2())),this));
                                relAscLayout->addLayout(coupleLayout);
                            }
                        }
                    }
                relAscWidget->setLayout(relAscLayout);
            scrollRelAsc->setWidget(relAscWidget);
            scrollRelAsc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelAsc);

        QLabel *labRelDesc = new QLabel("Relations Descendantes : ");
    rightLayout->addWidget(labRelDesc);

            scrollRelDesc = new QScrollArea;
                QWidget *relDescWidget = new QWidget;
                QVBoxLayout *relDescLayout = new QVBoxLayout;
                //Affiche les references descendantes
                //Donc l' ID de la note principale doit correspondre à l'id1 des couples
                relDescLayout->addWidget(new QLabel(manager.getReference().getTitre()));
                for(Relation::IteratorCouples itc=manager.getReference().getIteratorCouples();!itc.isDone();itc.next()){
                    if(notePrincipale->getID() == itc.current().getID1()){
                        QHBoxLayout *coupleLayout = new QHBoxLayout;
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1())),this));
                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2())),this));
                        relDescLayout->addLayout(coupleLayout);
                    }
                }
                //Affiche les relations descendantes
                //Donc l' ID de la note principale doit correspondre à l'id1 des couples des relations orientees et à l'un des deux id des couples des relations non orientees
                    for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next()){
                        relDescLayout->addWidget(new QLabel(itr.current().getTitre()));
                        for(Relation::IteratorCouples itc=itr.current().getIteratorCouples();!itc.isDone();itc.next()){
                            if((itr.current().isOrientee() && notePrincipale->getID() == itc.current().getID1()) || (!itr.current().isOrientee() && (notePrincipale->getID() == itc.current().getID1() || notePrincipale->getID() == itc.current().getID2()))){
                                QHBoxLayout *coupleLayout = new QHBoxLayout;
                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1())),this));
                                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2())),this));
                                relDescLayout->addLayout(coupleLayout);
                            }
                        }
                    }
                relDescWidget->setLayout(relDescLayout);
            scrollRelDesc->setWidget(relDescWidget);
            scrollRelDesc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelDesc);

    rightWidget->setLayout(rightLayout);
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

void FenetrePrincipale::updateScrollRelAsc(Note& n){
    Manager& manager = Manager::donneInstance();

    QScrollArea *newScrollRelAsc = new QScrollArea;
        QWidget *relAscWidget = new QWidget;
        QVBoxLayout *relAscLayout = new QVBoxLayout;
        //Affiche les references ascendantes
        //Donc l' ID de la note principale doit correspondre à l'id2 des couples
        relAscLayout->addWidget(new QLabel(manager.getReference().getTitre()));
        for(Relation::IteratorCouples itc=manager.getReference().getIteratorCouples();!itc.isDone();itc.next()){
            if(n.getID() == itc.current().getID2()){
                QHBoxLayout *coupleLayout = new QHBoxLayout;
                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1())),this));
                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2())),this));
                relAscLayout->addLayout(coupleLayout);
            }
        }
        //Affiche les relations ascendantes
        //Donc l' ID de la note principale doit correspondre à l'id2 des couples des relations orientees et à l'un des deux id des couples des relations non orientees
            for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next()){
                relAscLayout->addWidget(new QLabel(itr.current().getTitre()));
                for(Relation::IteratorCouples itc=itr.current().getIteratorCouples();!itc.isDone();itc.next()){
                    if((itr.current().isOrientee() && n.getID() == itc.current().getID2()) || (!itr.current().isOrientee() && (n.getID() == itc.current().getID1() || n.getID() == itc.current().getID2()))){
                        QHBoxLayout *coupleLayout = new QHBoxLayout;
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1())),this));
                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2())),this));
                        relAscLayout->addLayout(coupleLayout);
                    }
                }
            }
        relAscWidget->setLayout(relAscLayout);
    newScrollRelAsc->setWidget(relAscWidget);
    newScrollRelAsc->setWidgetResizable(true);

    QScrollArea *oldScrollRelAsc = scrollRelAsc;
    rightDockWidget->widget()->layout()->replaceWidget(scrollRelAsc,newScrollRelAsc);
    scrollRelAsc = newScrollRelAsc;
    delete oldScrollRelAsc;
}

void FenetrePrincipale::updateScrollRelDesc(Note& n){
    Manager& manager = Manager::donneInstance();

    QScrollArea *newScrollRelDesc = new QScrollArea;
        QWidget *relDescWidget = new QWidget;
        QVBoxLayout *relDescLayout = new QVBoxLayout;
        //Affiche les references descendantes
        //Donc l' ID de la note principale doit correspondre à l'id1 des couples
        relDescLayout->addWidget(new QLabel(manager.getReference().getTitre()));
        for(Relation::IteratorCouples itc=manager.getReference().getIteratorCouples();!itc.isDone();itc.next()){
            if(n.getID() == itc.current().getID1()){
                QHBoxLayout *coupleLayout = new QHBoxLayout;
                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1())),this));
                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2())),this));
                relDescLayout->addLayout(coupleLayout);
            }
        }
        //Affiche les relations descendantes
        //Donc l' ID de la note principale doit correspondre à l'id1 des couples des relations orientees et à l'un des deux id des couples des relations non orientees
            for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next()){
                relDescLayout->addWidget(new QLabel(itr.current().getTitre()));
                for(Relation::IteratorCouples itc=itr.current().getIteratorCouples();!itc.isDone();itc.next()){
                    if((itr.current().isOrientee() && n.getID() == itc.current().getID1()) || (!itr.current().isOrientee() && (n.getID() == itc.current().getID1() || n.getID() == itc.current().getID2()))){
                        QHBoxLayout *coupleLayout = new QHBoxLayout;
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1())),this));
                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2())),this));
                        relDescLayout->addLayout(coupleLayout);
                    }
                }
            }
        relDescWidget->setLayout(relDescLayout);
    newScrollRelDesc->setWidget(relDescWidget);
    newScrollRelDesc->setWidgetResizable(true);

    QScrollArea *oldScrollRelDesc = scrollRelDesc;
    rightDockWidget->widget()->layout()->replaceWidget(scrollRelDesc,newScrollRelDesc);
    scrollRelDesc = newScrollRelDesc;
    delete oldScrollRelDesc;
}

void FenetrePrincipale::changerNotePrincipale(Note &n){
    updateNotePrincipale(n);
    updateAutresVersions(n);
    updateScrollRelAsc(n);
    updateScrollRelDesc(n);
}
