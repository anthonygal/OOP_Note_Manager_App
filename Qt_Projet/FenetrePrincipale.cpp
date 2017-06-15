#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent){
    Manager& manager = Manager::donneInstance();

    //MENU
    QMenu *menuAfficher = menuBar()->addMenu("&Fichier");
        QAction *actionQuitter = new QAction("&Quitter");
        menuAfficher->addAction(actionQuitter);
    QMenu *menuNotes = menuBar()->addMenu("&Notes");
        QMenu *newNote = menuNotes->addMenu("Nouvelle note");
    QMenu *menuRelation = menuBar()->addMenu("&Relation");
        QMenu *newRelation = menuRelation->addMenu("&Nouvelle Relation");

            QAction *newArticle = new QAction("Article");
            QAction *newTache = new QAction("Tache");
            QAction *newMultimedia = new QAction("Multimedia");
            newNote->addAction(newArticle);
            newNote->addAction(newTache);
            newNote->addAction(newMultimedia);
    QMenu *menuCorbeille = menuBar()->addMenu("&Corbeille");
        QAction *actionViderCorbeille = new QAction("Vider la Corbeille");
        QAction *actionRestaurerCorbeille = new QAction("Restaurer la corbeille");
        menuCorbeille->addAction(actionViderCorbeille);
        menuCorbeille->addAction(actionRestaurerCorbeille);
        QObject::connect(actionViderCorbeille,SIGNAL(triggered()),this,SLOT(viderCorbeille()));
        QObject::connect(actionRestaurerCorbeille,SIGNAL(triggered()),this,SLOT(restaurerCorbeille()));


            QAction *newRel = new QAction("Creer Relation");
            QAction *newCouple = new QAction("Ajouter Couple");
            newRelation->addAction(newRel);
            newRelation->addAction(newCouple);
            QObject::connect(newCouple, SIGNAL(triggered()), this, SLOT(editRelation()));
            
    //DOCK WIDGET GAUCHE
    leftDockWidget = new QDockWidget("Toutes les notes");
    leftDockWidget->setStyleSheet("background-color: white");
    leftDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

        QWidget *leftWidget = new QWidget;
        QVBoxLayout *leftLayout = new QVBoxLayout;

            QLabel *notesActivesLab = new QLabel("Notes Actives :");
        leftLayout->addWidget(notesActivesLab);

            scrollAreaActives = new QScrollArea;
                QWidget *notesActivesWidget = new QWidget;
                QVBoxLayout *notesActivesLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next())
                    if(it.current().getEtat() == active && it.current().isActuelle())
                        notesActivesLayout->addWidget(new QNoteReduite(it.current()));
                notesActivesWidget->setLayout(notesActivesLayout);
            scrollAreaActives->setWidget(notesActivesWidget);
            scrollAreaActives->setWidgetResizable(true);
        leftLayout->addWidget(scrollAreaActives);

            QLabel *tachesTrieesLab = new QLabel("Taches triées :");
        leftLayout->addWidget(tachesTrieesLab);

            scrollTachesTriees = new QScrollArea;
                QWidget *tachesTrieesWidget = new QWidget;
                QVBoxLayout *tachesTrieesLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next())
                    if(it.current().getTypeNote()=="Tache" && it.current().getEtat()==active && it.current().isActuelle())
                        tachesTrieesLayout->addWidget(new QNoteReduite(it.current()));
                tachesTrieesWidget->setLayout(tachesTrieesLayout);
            scrollTachesTriees->setWidget(tachesTrieesWidget);
            scrollTachesTriees->setWidgetResizable(true);
        leftLayout->addWidget(scrollTachesTriees);

            QLabel *notesArchiveesLab = new QLabel("Notes Archivées :");
        leftLayout->addWidget(notesArchiveesLab);

            scrollAreaArchivees = new QScrollArea;
                QWidget *notesArchiveesWidget = new QWidget;
                QVBoxLayout *notesArchiveesLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next())
                    if(it.current().getEtat() == archivee && it.current().isActuelle())
                        notesArchiveesLayout->addWidget(new QNoteReduite(it.current()));
                notesArchiveesWidget->setLayout(notesArchiveesLayout);
            scrollAreaArchivees->setWidget(notesArchiveesWidget);
            scrollAreaArchivees->setWidgetResizable(true);
        leftLayout->addWidget(scrollAreaArchivees);

        leftWidget->setLayout(leftLayout);
    leftDockWidget->setWidget(leftWidget);
    addDockWidget(Qt::LeftDockWidgetArea,leftDockWidget);
    //FIN DOCK WIDGET GAUCHE


    //ZONE CENTRALE
    zoneCentrale = new QWidget;
    centralLayout = new QVBoxLayout;

        QLabel *notePrincipaleLab = new QLabel("Note Principale :");
    centralLayout->addWidget(notePrincipaleLab);

        Manager::IteratorNotes it=manager.getIteratorNotes();
        while(!it.isDone() && it.current().getEtat() != active && !it.current().isActuelle())
            it.next();
        notePrincipale = new QNote(it.current());
    centralLayout->addWidget(notePrincipale);

        QLabel *autresVersionsLab = new QLabel("Les autres versions de la note :");
    centralLayout->addWidget(autresVersionsLab);

        autresVersions = new QScrollArea;
            QWidget *autresVerWidget = new QWidget;
            QVBoxLayout *autresVerLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it2=manager.getIteratorNotes();!it2.isDone();it2.next()){
                    if(it2.current().getID() == it.current().getID() && it2.current().getDateModif() != it.current().getDateModif()){
                        QHBoxLayout *hlayout = new QHBoxLayout;
                            hlayout->addWidget(new QLabel(it2.current().getDateModif().toString(formatDateTime)));
                            hlayout->addWidget(new QNoteReduite(it2.current()));
                        autresVerLayout->addLayout(hlayout);
                    }
                }
            autresVerWidget->setLayout(autresVerLayout);
        autresVersions->setWidget(autresVerWidget);
        autresVersions->setWidgetResizable(true);
    centralLayout->addWidget(autresVersions);

    zoneCentrale->setLayout(centralLayout);
    setCentralWidget(zoneCentrale);
    //FIN ZONE CENTRALE

    //DOCK WIDGET DROIT
    rightDockWidget = new QDockWidget("Relations de la note principale");
        QWidget *rightWidget = new QWidget;
        QVBoxLayout *rightLayout = new QVBoxLayout;

            QLabel *labRelAsc = new QLabel("Relations Ascendantes : ");
        rightLayout->addWidget(labRelAsc);

            scrollRelAsc = new QScrollArea;
                QLabel *relAscWidget = new QLabel("Aucune Relation");
//                QVBoxLayout *relAscLayout = new QVBoxLayout;
//                //Affiche les references ascendantes
//                //Donc l' ID de la note principale doit correspondre à l'id2 des couples
//                relAscLayout->addWidget(new QLabel(manager.getReference().getTitre()));
//                for(Relation::IteratorCouples itc=manager.getReference().getIteratorCouples();!itc.isDone();itc.next()){
//                    if(notePrincipale->getID() == itc.current().getID2()){
//                        QHBoxLayout *coupleLayout = new QHBoxLayout;
//                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
//                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
//                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
//                        relAscLayout->addLayout(coupleLayout);
//                    }
//                }
//                //Affiche les relations ascendantes
//                //Donc l' ID de la note principale doit correspondre à l'id2 des couples des relations orientees et à l'un des deux id des couples des relations non orientees
//                    for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next()){
//                        relAscLayout->addWidget(new QLabel(itr.current().getTitre()));
//                        for(Relation::IteratorCouples itc=itr.current().getIteratorCouples();!itc.isDone();itc.next()){
//                            if((itr.current().isOrientee() && notePrincipale->getID() == itc.current().getID2()) || (!itr.current().isOrientee() && (notePrincipale->getID() == itc.current().getID1() || notePrincipale->getID() == itc.current().getID2()))){
//                                QHBoxLayout *coupleLayout = new QHBoxLayout;
//                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
//                                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
//                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
//                                relAscLayout->addLayout(coupleLayout);
//                            }
//                        }
//                    }
//                relAscWidget->setLayout(relAscLayout);
            scrollRelAsc->setWidget(relAscWidget);
            scrollRelAsc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelAsc);

        QLabel *labRelDesc = new QLabel("Relations Descendantes : ");
    rightLayout->addWidget(labRelDesc);

            scrollRelDesc = new QScrollArea;
                QLabel *relDescWidget = new QLabel("Aucune relation");
//                QVBoxLayout *relDescLayout = new QVBoxLayout;
                //Affiche les references descendantes
                //Donc l' ID de la note principale doit correspondre à l'id1 des couples
//                relDescLayout->addWidget(new QLabel(manager.getReference().getTitre()));
//                for(Relation::IteratorCouples itc=manager.getReference().getIteratorCouples();!itc.isDone();itc.next()){
//                    if(notePrincipale->getID() == itc.current().getID1()){
//                        QHBoxLayout *coupleLayout = new QHBoxLayout;
//                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
//                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
//                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
//                        relDescLayout->addLayout(coupleLayout);
//                    }
//                }
                //Affiche les relations descendantes
                //Donc l' ID de la note principale doit correspondre à l'id1 des couples des relations orientees et à l'un des deux id des couples des relations non orientees
//                    for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next()){
//                        relDescLayout->addWidget(new QLabel(itr.current().getTitre()));
//                        for(Relation::IteratorCouples itc=itr.current().getIteratorCouples();!itc.isDone();itc.next()){
//                            if((itr.current().isOrientee() && notePrincipale->getID() == itc.current().getID1()) || (!itr.current().isOrientee() && (notePrincipale->getID() == itc.current().getID1() || notePrincipale->getID() == itc.current().getID2()))){
//                                QHBoxLayout *coupleLayout = new QHBoxLayout;
//                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
//                                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
//                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
//                                relDescLayout->addLayout(coupleLayout);
//                            }
//                        }
//                    }
//                relDescWidget->setLayout(relDescLayout);
            scrollRelDesc->setWidget(relDescWidget);
            scrollRelDesc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelDesc);

    rightWidget->setLayout(rightLayout);
    rightDockWidget->setWidget(rightWidget);
    addDockWidget(Qt::RightDockWidgetArea,rightDockWidget);
    //FIN DOCK WIDGET DROIT
}

FenetrePrincipale::~FenetrePrincipale(){
    delete leftDockWidget;
    delete notePrincipale;
    delete autresVersions;
    delete rightDockWidget;
    delete scrollRelAsc;
    delete scrollRelDesc;
}

/**< TEMPLATE METHOD SINGLETON POUR LA CLASS FENETREPRINCIPALE */

FenetrePrincipale* FenetrePrincipale::instanceUnique=nullptr;

FenetrePrincipale& FenetrePrincipale::donneInstance(){
    if (instanceUnique==nullptr) instanceUnique = new FenetrePrincipale;
    return *instanceUnique;
}

void FenetrePrincipale::libereInstance(){
    if (instanceUnique!=nullptr)
        delete instanceUnique;
    instanceUnique=nullptr;
}

/**< Methodes d'update de la fenetre */

void FenetrePrincipale::updateScrollAreaActives(){
    QScrollArea *newScrollAreaActives = new QScrollArea;
        QWidget *notesActivesWidget = new QWidget;
        QVBoxLayout *notesActivesLayout = new QVBoxLayout;
        for(Manager::IteratorNotes it=Manager::donneInstance().getIteratorNotes();!it.isDone();it.next())
            if(it.current().getEtat() == active && it.current().isActuelle())
                notesActivesLayout->addWidget(new QNoteReduite(it.current()));
        notesActivesWidget->setLayout(notesActivesLayout);
    newScrollAreaActives->setWidget(notesActivesWidget);
    newScrollAreaActives->setWidgetResizable(true);

    QScrollArea *oldScrollAreaActives = scrollAreaActives;
    leftDockWidget->widget()->layout()->replaceWidget(scrollAreaActives,newScrollAreaActives);
    scrollAreaActives = newScrollAreaActives;
    delete oldScrollAreaActives;
}

void FenetrePrincipale::updateTachesTriees(){
    QScrollArea *newScrollTachesTriees = new QScrollArea;
        QWidget *tachesTrieesWidget = new QWidget;
        QVBoxLayout *tachesTrieesLayout = new QVBoxLayout;
        for(Manager::IteratorNotes it=Manager::donneInstance().getIteratorNotes();!it.isDone();it.next())
            if(it.current().getTypeNote()=="Tache" && it.current().getEtat()==active && it.current().isActuelle())
                tachesTrieesLayout->addWidget(new QNoteReduite(it.current()));
        tachesTrieesWidget->setLayout(tachesTrieesLayout);
    newScrollTachesTriees->setWidget(tachesTrieesWidget);
    newScrollTachesTriees->setWidgetResizable(true);

    QScrollArea *oldScrollTachesTriees = scrollTachesTriees;
    leftDockWidget->widget()->layout()->replaceWidget(scrollTachesTriees,newScrollTachesTriees);
    scrollTachesTriees = newScrollTachesTriees;
    delete oldScrollTachesTriees;
}

void FenetrePrincipale::updateScrollAreaArchivees(){
    QScrollArea *newScrollAreaArchivees = new QScrollArea;
    QWidget *notesArchiveesWidget = new QWidget;
        QVBoxLayout *notesArchiveesLayout = new QVBoxLayout;
        for(Manager::IteratorNotes it=Manager::donneInstance().getIteratorNotes();!it.isDone();it.next())
            if(it.current().getEtat() == archivee && it.current().isActuelle())
                notesArchiveesLayout->addWidget(new QNoteReduite(it.current()));
        notesArchiveesWidget->setLayout(notesArchiveesLayout);
    newScrollAreaArchivees->setWidget(notesArchiveesWidget);
    newScrollAreaArchivees->setWidgetResizable(true);

    QScrollArea *oldScrollAreaArchivees = scrollAreaArchivees;
    leftDockWidget->widget()->layout()->replaceWidget(scrollAreaArchivees,newScrollAreaArchivees);
    scrollAreaArchivees = newScrollAreaArchivees;
    delete oldScrollAreaArchivees;
}

void FenetrePrincipale::updateNotePrincipale(Note& n){
    QNote *oldNotePrincipale = notePrincipale;
    QNote *newNotePrincipale = new QNote(n);
    centralWidget()->layout()->replaceWidget(notePrincipale, newNotePrincipale);
    notePrincipale = newNotePrincipale;
    delete oldNotePrincipale;
}

void FenetrePrincipale::updateNotePrincipale(){
    QNote *oldNotePrincipale = notePrincipale;
    QNote *newNotePrincipale = nullptr;
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
                        hlayout->addWidget(new QNoteReduite(it.current()));
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

void FenetrePrincipale::updateAutresVersions(){
    QScrollArea *oldAutreVersions = autresVersions;

    QScrollArea *newAutresVersions = new QScrollArea;
        QLabel *autresVerWidget = new QLabel("Aucune autre version pour cette note");
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
                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
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
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
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

void FenetrePrincipale::updateScrollRelAsc(){
    Manager& manager = Manager::donneInstance();

    QScrollArea *newScrollRelAsc = new QScrollArea;
        QWidget *relAscWidget = new QWidget;
        QVBoxLayout *relAscLayout = new QVBoxLayout;
        relAscLayout->addWidget(new QLabel(manager.getReference().getTitre()));
        for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next())
            relAscLayout->addWidget(new QLabel(itr.current().getTitre()));
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
                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
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
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
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

void FenetrePrincipale::updateScrollRelDesc(){
    Manager& manager = Manager::donneInstance();

    QScrollArea *newScrollRelDesc = new QScrollArea;
        QWidget *relDescWidget = new QWidget;
        QVBoxLayout *relDescLayout = new QVBoxLayout;
        relDescLayout->addWidget(new QLabel(manager.getReference().getTitre()));
        for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next())
            relDescLayout->addWidget(new QLabel(itr.current().getTitre()));
        relDescWidget->setLayout(relDescLayout);
    newScrollRelDesc->setWidget(relDescWidget);
    newScrollRelDesc->setWidgetResizable(true);

    QScrollArea *oldScrollRelDesc = scrollRelDesc;
    rightDockWidget->widget()->layout()->replaceWidget(scrollRelDesc,newScrollRelDesc);
    scrollRelDesc = newScrollRelDesc;
    delete oldScrollRelDesc;
}

void FenetrePrincipale::updateFenetre(Note &n){
    updateScrollAreaActives();
    updateTachesTriees();
    updateScrollAreaArchivees();
    updateNotePrincipale(n);
    updateAutresVersions(n);
    updateScrollRelAsc(n);
    updateScrollRelDesc(n);
}


 void FenetrePrincipale::editRelation(){
    RelationEditeur* re= new RelationEditeur(zoneCentrale);
    //centralLayout->removeWidget(notePrincipale);
    setCentralWidget(re);
    delete leftDockWidget;
    delete rightDockWidget;
    //centralLayout->addWidget(re);

 }

void FenetrePrincipale::updateFenetre(){
    updateScrollAreaActives();
    updateTachesTriees();
    updateScrollAreaArchivees();
    updateNotePrincipale();
    updateAutresVersions();
    updateScrollRelAsc();
    updateScrollRelDesc();
}

void FenetrePrincipale::viderCorbeille(){
    Manager::donneInstance().viderCorbeille();
    if(Manager::donneInstance().getNbNotes() == 0) updateFenetre();
    else updateFenetre(Manager::donneInstance().getIteratorNotes().current());
    QMessageBox::information(this,"Corbeille","La corbeille a été vidée");
}

void FenetrePrincipale::restaurerCorbeille(){
    Manager::donneInstance().restaurerCorbeille();
    updateFenetre(notePrincipale->getNote());
    QMessageBox::information(this,"Corbeille","La corbeille a été restaurée");
}

void FenetrePrincipale::reaffichageNote(){
    Manager& manager = Manager::donneInstance();
    leftDockWidget = new QDockWidget("Toutes les notes");
    leftDockWidget->setStyleSheet("background-color: white");
    leftDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

        QWidget *leftWidget = new QWidget;
        QVBoxLayout *leftLayout = new QVBoxLayout;

            QLabel *notesActivesLab = new QLabel("Notes Actives :");
        leftLayout->addWidget(notesActivesLab);

            scrollAreaActives = new QScrollArea;
                QWidget *notesActivesWidget = new QWidget;
                QVBoxLayout *notesActivesLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next())
                    if(it.current().getEtat() == active && it.current().isActuelle())
                        notesActivesLayout->addWidget(new QNoteReduite(it.current()));
                notesActivesWidget->setLayout(notesActivesLayout);
            scrollAreaActives->setWidget(notesActivesWidget);
            scrollAreaActives->setWidgetResizable(true);
        leftLayout->addWidget(scrollAreaActives);

            QLabel *tachesTrieesLab = new QLabel("Taches triées :");
        leftLayout->addWidget(tachesTrieesLab);

            scrollTachesTriees = new QScrollArea;
                QWidget *tachesTrieesWidget = new QWidget;
                QVBoxLayout *tachesTrieesLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next())
                    if(it.current().getTypeNote()=="Tache" && it.current().getEtat()==active && it.current().isActuelle())
                        tachesTrieesLayout->addWidget(new QNoteReduite(it.current()));
                tachesTrieesWidget->setLayout(tachesTrieesLayout);
            scrollTachesTriees->setWidget(tachesTrieesWidget);
            scrollTachesTriees->setWidgetResizable(true);
        leftLayout->addWidget(scrollTachesTriees);

            QLabel *notesArchiveesLab = new QLabel("Notes Archivées :");
        leftLayout->addWidget(notesArchiveesLab);

            scrollAreaArchivees = new QScrollArea;
                QWidget *notesArchiveesWidget = new QWidget;
                QVBoxLayout *notesArchiveesLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it=manager.getIteratorNotes();!it.isDone();it.next())
                    if(it.current().getEtat() == archivee && it.current().isActuelle())
                        notesArchiveesLayout->addWidget(new QNoteReduite(it.current()));
                notesArchiveesWidget->setLayout(notesArchiveesLayout);
            scrollAreaArchivees->setWidget(notesArchiveesWidget);
            scrollAreaArchivees->setWidgetResizable(true);
        leftLayout->addWidget(scrollAreaArchivees);

        leftWidget->setLayout(leftLayout);
    leftDockWidget->setWidget(leftWidget);
    addDockWidget(Qt::LeftDockWidgetArea,leftDockWidget);
    //FIN DOCK WIDGET GAUCHE


    //ZONE CENTRALE
    zoneCentrale = new QWidget;
    centralLayout = new QVBoxLayout;

        QLabel *notePrincipaleLab = new QLabel("Note Principale :");
    centralLayout->addWidget(notePrincipaleLab);

        Manager::IteratorNotes it=manager.getIteratorNotes();
        while(!it.isDone() && it.current().getEtat() != active && !it.current().isActuelle())
            it.next();
        notePrincipale = new QNote(it.current());
    centralLayout->addWidget(notePrincipale);

        QLabel *autresVersionsLab = new QLabel("Les autres versions de la note :");
    centralLayout->addWidget(autresVersionsLab);

        autresVersions = new QScrollArea;
            QWidget *autresVerWidget = new QWidget;
            QVBoxLayout *autresVerLayout = new QVBoxLayout;
                for(Manager::IteratorNotes it2=manager.getIteratorNotes();!it2.isDone();it2.next()){
                    if(it2.current().getID() == it.current().getID() && it2.current().getDateModif() != it.current().getDateModif()){
                        QHBoxLayout *hlayout = new QHBoxLayout;
                            hlayout->addWidget(new QLabel(it2.current().getDateModif().toString(formatDateTime)));
                            hlayout->addWidget(new QNoteReduite(it2.current()));
                        autresVerLayout->addLayout(hlayout);
                    }
                }
            autresVerWidget->setLayout(autresVerLayout);
        autresVersions->setWidget(autresVerWidget);
        autresVersions->setWidgetResizable(true);
    centralLayout->addWidget(autresVersions);

    zoneCentrale->setLayout(centralLayout);
    setCentralWidget(zoneCentrale);
    //FIN ZONE CENTRALE

    //DOCK WIDGET DROIT
    rightDockWidget = new QDockWidget("Relations de la note principale");
        QWidget *rightWidget = new QWidget;
        QVBoxLayout *rightLayout = new QVBoxLayout;

            QLabel *labRelAsc = new QLabel("Relations Ascendantes : ");
        rightLayout->addWidget(labRelAsc);

            scrollRelAsc = new QScrollArea;
                QLabel *relAscWidget = new QLabel("Aucune Relation");
//                QVBoxLayout *relAscLayout = new QVBoxLayout;
//                //Affiche les references ascendantes
//                //Donc l' ID de la note principale doit correspondre à l'id2 des couples
//                relAscLayout->addWidget(new QLabel(manager.getReference().getTitre()));
//                for(Relation::IteratorCouples itc=manager.getReference().getIteratorCouples();!itc.isDone();itc.next()){
//                    if(notePrincipale->getID() == itc.current().getID2()){
//                        QHBoxLayout *coupleLayout = new QHBoxLayout;
//                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
//                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
//                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
//                        relAscLayout->addLayout(coupleLayout);
//                    }
//                }
//                //Affiche les relations ascendantes
//                //Donc l' ID de la note principale doit correspondre à l'id2 des couples des relations orientees et à l'un des deux id des couples des relations non orientees
//                    for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next()){
//                        relAscLayout->addWidget(new QLabel(itr.current().getTitre()));
//                        for(Relation::IteratorCouples itc=itr.current().getIteratorCouples();!itc.isDone();itc.next()){
//                            if((itr.current().isOrientee() && notePrincipale->getID() == itc.current().getID2()) || (!itr.current().isOrientee() && (notePrincipale->getID() == itc.current().getID1() || notePrincipale->getID() == itc.current().getID2()))){
//                                QHBoxLayout *coupleLayout = new QHBoxLayout;
//                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
//                                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
//                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
//                                relAscLayout->addLayout(coupleLayout);
//                            }
//                        }
//                    }
//                relAscWidget->setLayout(relAscLayout);
            scrollRelAsc->setWidget(relAscWidget);
            scrollRelAsc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelAsc);

        QLabel *labRelDesc = new QLabel("Relations Descendantes : ");
    rightLayout->addWidget(labRelDesc);

            scrollRelDesc = new QScrollArea;
                QLabel *relDescWidget = new QLabel("Aucune relation");
//                QVBoxLayout *relDescLayout = new QVBoxLayout;
                //Affiche les references descendantes
                //Donc l' ID de la note principale doit correspondre à l'id1 des couples
//                relDescLayout->addWidget(new QLabel(manager.getReference().getTitre()));
//                for(Relation::IteratorCouples itc=manager.getReference().getIteratorCouples();!itc.isDone();itc.next()){
//                    if(notePrincipale->getID() == itc.current().getID1()){
//                        QHBoxLayout *coupleLayout = new QHBoxLayout;
//                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
//                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
//                        coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
//                        relDescLayout->addLayout(coupleLayout);
//                    }
//                }
                //Affiche les relations descendantes
                //Donc l' ID de la note principale doit correspondre à l'id1 des couples des relations orientees et à l'un des deux id des couples des relations non orientees
//                    for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next()){
//                        relDescLayout->addWidget(new QLabel(itr.current().getTitre()));
//                        for(Relation::IteratorCouples itc=itr.current().getIteratorCouples();!itc.isDone();itc.next()){
//                            if((itr.current().isOrientee() && notePrincipale->getID() == itc.current().getID1()) || (!itr.current().isOrientee() && (notePrincipale->getID() == itc.current().getID1() || notePrincipale->getID() == itc.current().getID2()))){
//                                QHBoxLayout *coupleLayout = new QHBoxLayout;
//                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))));
//                                coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
//                                coupleLayout->addWidget(new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))));
//                                relDescLayout->addLayout(coupleLayout);
//                            }
//                        }
//                    }
//                relDescWidget->setLayout(relDescLayout);
            scrollRelDesc->setWidget(relDescWidget);
            scrollRelDesc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelDesc);

    rightWidget->setLayout(rightLayout);
    rightDockWidget->setWidget(rightWidget);
    addDockWidget(Qt::RightDockWidgetArea,rightDockWidget);
    //FIN DOCK WIDGET DROIT
}

