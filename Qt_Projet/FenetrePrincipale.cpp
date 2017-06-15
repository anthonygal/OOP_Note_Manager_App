#include "FenetrePrincipale.h"
#include "NewNote.h"

FenetrePrincipale* FenetrePrincipale::instanceUnique=nullptr;

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent){
    Manager& manager = Manager::donneInstance();

    //MENU
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
        QAction *revenirVuePrincipal = new QAction("Revenir à la vue principal");
        QAction *actionSauvegarder = new QAction("&Sauvegarder");
        QAction *actionQuitter = new QAction("&Quitter");
        menuFichier->addAction(revenirVuePrincipal);
        menuFichier->addAction(actionSauvegarder);
        menuFichier->addAction(actionQuitter);

    QObject::connect(revenirVuePrincipal,SIGNAL(triggered()),this,SLOT(reaffichageNote()));
    QObject::connect(actionSauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarder()));
    QObject::connect(actionQuitter,SIGNAL(triggered()),this,SLOT(close()));

    QMenu *menuNotes = menuBar()->addMenu("&Notes");
        QMenu *newNote = menuNotes->addMenu("Nouvelle note");
            QAction *newArticle = new QAction("Article");
            QAction *newTache = new QAction("Tache");
            QAction *newMultimedia = new QAction("Multimedia");
            newNote->addAction(newArticle);
            newNote->addAction(newTache);
            newNote->addAction(newMultimedia);

    QObject::connect(newArticle,SIGNAL(triggered()),this,SLOT(newArticle()));
    QObject::connect(newTache,SIGNAL(triggered()),this,SLOT(newTache()));
    QObject::connect(newMultimedia,SIGNAL(triggered()),this,SLOT(newMultimedia()));

    QMenu *menuRelation = menuBar()->addMenu("&Relation");
        QAction *voirRelations = new QAction("Voir toutes les relations");
        QAction *newRel = new QAction("Creer Relation");
        QAction *newCouple = new QAction("Ajouter Couple");
        menuRelation->addAction(voirRelations);
        menuRelation->addAction(newRel);
        menuRelation->addAction(newCouple);

    QObject::connect(voirRelations, SIGNAL(triggered()), this, SLOT(voirRelations()));
    QObject::connect(newCouple, SIGNAL(triggered()), this, SLOT(editRelation()));
    QObject::connect(newRel,SIGNAL(triggered()), this, SLOT(createRelation()));

    QMenu *menuCorbeille = menuBar()->addMenu("&Corbeille");
        QAction *actionViderCorbeille = new QAction("Vider la Corbeille");
        QAction *actionRestaurerCorbeille = new QAction("Restaurer la corbeille");
        menuCorbeille->addAction(actionViderCorbeille);
        menuCorbeille->addAction(actionRestaurerCorbeille);

    QObject::connect(actionViderCorbeille,SIGNAL(triggered()),this,SLOT(viderCorbeille()));
    QObject::connect(actionRestaurerCorbeille,SIGNAL(triggered()),this,SLOT(restaurerCorbeille()));
    //FIN MENU

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
    QWidget *zoneCentrale = new QWidget;
    QVBoxLayout *centralLayout = new QVBoxLayout;

        QLabel *notePrincipaleLab = new QLabel("Note Principale :");
    centralLayout->addWidget(notePrincipaleLab);

        notePrincipale = new QLabel("Aucune note selectionnée");
    centralLayout->addWidget(notePrincipale);

        QLabel *autresVersionsLab = new QLabel("Les autres versions de la note :");
    centralLayout->addWidget(autresVersionsLab);

        autresVersions = new QScrollArea;
            QLabel *autresVerWidget = new QLabel("Aucune note selectionnée");
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
                QLabel *relAscWidget = new QLabel("Aucune note selectionnée");
            scrollRelAsc->setWidget(relAscWidget);
            scrollRelAsc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelAsc);

            QLabel *labRelDesc = new QLabel("Relations Descendantes : ");
        rightLayout->addWidget(labRelDesc);

            scrollRelDesc = new QScrollArea;
                QLabel *relDescWidget = new QLabel("Aucune note selectionnée");
            scrollRelDesc->setWidget(relDescWidget);
            scrollRelDesc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelDesc);

    rightWidget->setLayout(rightLayout);
    rightDockWidget->setWidget(rightWidget);
    addDockWidget(Qt::RightDockWidgetArea,rightDockWidget);
    //FIN DOCK WIDGET DROIT
}

FenetrePrincipale& FenetrePrincipale::donneInstance(){
    if (instanceUnique==nullptr) instanceUnique = new FenetrePrincipale;
    return *instanceUnique;
}

void FenetrePrincipale::libereInstance(){
    if (instanceUnique!=nullptr)
        delete instanceUnique;
    instanceUnique=nullptr;
}

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
    QWidget *oldNotePrincipale = notePrincipale;
    QWidget *newNotePrincipale = new QNote(n);
    centralWidget()->layout()->replaceWidget(notePrincipale, newNotePrincipale);
    notePrincipale = newNotePrincipale;
    delete oldNotePrincipale;
}

void FenetrePrincipale::updateNotePrincipale(){
    QWidget *oldNotePrincipale = notePrincipale;
    QWidget *newNotePrincipale = new QLabel("Aucune note selectionnée");
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
        QLabel *autresVerWidget = new QLabel("Aucune note selectionnée");
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
    QScrollArea *newScrollRelAsc = new QScrollArea;
        QLabel *relAscWidget = new QLabel("Aucune note selectionnée");
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
    QScrollArea *newScrollRelDesc = new QScrollArea;
        QLabel *relDescWidget = new QLabel("Aucune note selectionnée");
    newScrollRelDesc->setWidget(relDescWidget);
    newScrollRelDesc->setWidgetResizable(true);

    QScrollArea *oldScrollRelDesc = scrollRelDesc;
    rightDockWidget->widget()->layout()->replaceWidget(scrollRelDesc,newScrollRelDesc);
    scrollRelDesc = newScrollRelDesc;
    delete oldScrollRelDesc;
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
    QWidget *zoneCentrale = new QWidget;
    QVBoxLayout *centralLayout = new QVBoxLayout;

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
            scrollRelAsc->setWidget(relAscWidget);
            scrollRelAsc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelAsc);

        QLabel *labRelDesc = new QLabel("Relations Descendantes : ");
    rightLayout->addWidget(labRelDesc);

            scrollRelDesc = new QScrollArea;
                QLabel *relDescWidget = new QLabel("Aucune relation");
            scrollRelDesc->setWidget(relDescWidget);
            scrollRelDesc->setWidgetResizable(true);
        rightLayout->addWidget(scrollRelDesc);

    rightWidget->setLayout(rightLayout);
    rightDockWidget->setWidget(rightWidget);
    addDockWidget(Qt::RightDockWidgetArea,rightDockWidget);
    //FIN DOCK WIDGET DROIT
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

void FenetrePrincipale::updateFenetre(){
    updateScrollAreaActives();
    updateTachesTriees();
    updateScrollAreaArchivees();
    updateNotePrincipale();
    updateAutresVersions();
    updateScrollRelAsc();
    updateScrollRelDesc();
}

void FenetrePrincipale::sauvegarder(){
    try{
        Manager::donneInstance().save();
        QMessageBox::information(this,"Sauvegarde","Les changements ont bien été sauvegardés");
    }catch(NoteException e){QMessageBox::critical(this,"Erreur",e.getInfo());}
}

void FenetrePrincipale::newArticle(){
    NewArticle *nouvelleNote = new NewArticle;
    nouvelleNote->show();
}

void FenetrePrincipale::newTache(){
    NewTache *nouvelleNote = new NewTache;
    nouvelleNote->show();
}

void FenetrePrincipale::newMultimedia(){
    NewMultimedia *nouvelleNote = new NewMultimedia;
    nouvelleNote->show();
}

void FenetrePrincipale::voirRelations(){
    Manager& manager = Manager::donneInstance();

    QScrollArea *zoneCentrale = new QScrollArea;
        QWidget *widget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;
            for(Manager::IteratorRelations itr=manager.getIteratorRelations();!itr.isDone();itr.next()){
                QHBoxLayout *layoutrel = new QHBoxLayout;
                    layoutrel->addWidget(new QLabel(itr.current().getTitre()));
                    layoutrel->addWidget(new QLabel(itr.current().isOrientee()?"Orientee":"Non Orientee"));
                layout->addLayout(layoutrel);
                for(Relation::ConstIteratorCouples itc=itr.current().getConstIteratorCouples();!itc.isDone();itc.next()){
                        QHBoxLayout *coupleLayout = new QHBoxLayout;
                        QNoteReduite *q1 = new QNoteReduite(*(manager.getNoteID(itc.current().getID1()))); q1->setEnabled(false); q1->setStyleSheet("color: black");
                        coupleLayout->addWidget(q1);
                        QLabel *lab = new QLabel(itc.current().getLabel()); lab->setAlignment(Qt::AlignCenter);
                        coupleLayout->addWidget(new QLabel(itc.current().getLabel()));
                        QNoteReduite *q2 = new QNoteReduite(*(manager.getNoteID(itc.current().getID2()))); q2->setEnabled(false); q2->setStyleSheet("color: black");
                        coupleLayout->addWidget(q1);
                        coupleLayout->addWidget(q2);
                        layout->addLayout(coupleLayout);
                }
            }
    widget->setLayout(layout);
    zoneCentrale->setWidget(widget);
    zoneCentrale->setWidgetResizable(true);

    setCentralWidget(zoneCentrale);
    delete leftDockWidget;
    delete rightDockWidget;
}

void FenetrePrincipale::editRelation(){
    RelationEditeur* rel = new RelationEditeur;
    setCentralWidget(rel);
    delete leftDockWidget;
    delete rightDockWidget;
}

void FenetrePrincipale::createRelation(){
     RelationCreateur* cr = new RelationCreateur();
     cr->show();
}

void FenetrePrincipale::viderCorbeille(){
    Manager::donneInstance().viderCorbeille();
    if(Manager::donneInstance().getNbNotes() == 0) updateFenetre();
    else updateFenetre(Manager::donneInstance().getIteratorNotes().current());
    QMessageBox::information(this,"Corbeille","La corbeille a été vidée");
}

void FenetrePrincipale::restaurerCorbeille(){
    Manager::donneInstance().restaurerCorbeille();
    if(Manager::donneInstance().getNbNotes() == 0) updateFenetre();
    else updateFenetre(Manager::donneInstance().getIteratorNotes().current());
    QMessageBox::information(this,"Corbeille","La corbeille a été restaurée");
}

