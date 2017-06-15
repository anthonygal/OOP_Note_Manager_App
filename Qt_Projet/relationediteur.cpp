#include "Relations.h"
#include "relationediteur.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QApplication>
#include "FenetrePrincipale.h"


///Definition des slots de relation editeur

///Slot permettant d'ajouter un couple à une relation.
void RelationEditeur::addCouple(){
    ///On récupère la note n1 dans le QlistWidget listNotesLeft
    QListWidgetItem* selectedItem1 = listNotesGauche->currentItem();
    QString titre1 = selectedItem1->text();
    int n1 = Manager::donneInstance().getIDNoteWithTitre(titre1);
    
    ///On récupère la note n2 dans le QlistWidget listNotesRight
    QListWidgetItem* selectedItem2 = listNotesDroite->currentItem();
    QString titre2 = selectedItem2->text();
    int n2= Manager::donneInstance().getIDNoteWithTitre(titre2);
    
     QListWidgetItem* selectedItem3 = listRelation->currentItem();
     QString titre3 = selectedItem3->text();
     Relation* r=Manager::donneInstance().getRelationWithTitre(titre3);

     QString Label = LineCouple->text();

     r->addCouple(n1, n2, Label);
    
    
    ///MessageBox attestant du succès de l'ajout de la relation
    QMessageBox::information(this, "Succès", "Le Couple a bien été ajouté à la relation");
}



///Slot permettant d'ajouter une relation non orientée.
///
/*
void RelationEditeur::addRelationNotOriented(){
    ///On récupère la note n1 dans le QlistWidget listNotesLeft
    QListWidgetItem* selectedItem1 = listNotesLeft->currentItem();
    QString title1 = selectedItem1->text();
    Note* n1 = NotesManager::getInstance().getNoteWithTitle(title1);
    ///On récupère la note n2 dans le QlistWidget listNotesRight
    QListWidgetItem* selectedItem2 = listNotesRight->currentItem();
    QString title2 = selectedItem2->text();
    Note* n2 = NotesManager::getInstance().getNoteWithTitle(title2);
    ///Création d'une relation de n1 vers n2
    Relation* r1 = new Relation;
    (*r1).addRelation(*n1,*n2);
    ///Création d'une relation de n2 vers n1
    Relation* r2 = new Relation;
    (*r2).addRelation(*n2,*n1);
    ///Insertion des deux relations dans RelationsManager
    RelationsManager& rm = RelationsManager::getInstance();
    if(!rm.isAlreadyPresent(*r1)){rm.addRelation(r1);}
    if(!rm.isAlreadyPresent(*r2)){rm.addRelation(r2);}
    ///MessageBox attestant du succès de l'ajout de la relation non orientée
    QMessageBox::information(this, "Succès", "La relation non orientée a bien été ajoutée");
}
*/

///Slot permettant de rendre les boutons cliquables
/*void RelationEditeur::enablePushButons(){
    add->setEnabled(true);
    addNotOriented->setEnabled(true);
}
*/

RelationEditeur::RelationEditeur(QWidget* parent){

    QGridLayout *layout = new QGridLayout;
    
    ///Premier QlistWidget : listNotesLeft
    listNotesGauche = new QListWidget();
    QListWidgetItem* item1;
    ///Second QlistWidget : listNotesRight
    listNotesDroite = new QListWidget();
    QListWidgetItem* item2;
    
    Manager& m = Manager::donneInstance();
    
    ///Remplissage de listNotes Gauche et Droite
    for(Manager::IteratorNotes it =m.getIteratorNotes(); !it.isDone(); it.next()){
        if (it.current().isActuelle()){
        item1 = new QListWidgetItem(it.current().getTitre(),listNotesGauche);
        item2 = new QListWidgetItem(it.current().getTitre(),listNotesDroite);
        }
    }
    
    listRelation = new QListWidget();
     QListWidgetItem* itemrel;
    for(Manager::IteratorRelations it2 =m.getIteratorRelations(); !it2.isDone(); it2.next()){
        itemrel = new QListWidgetItem(it2.current().getTitre() ,listRelation);

         }

    Lab= new QLabel("Quel est le label du couple?");
    LineCouple= new QLineEdit;

    
    layer = new QVBoxLayout();
    scroller = new QScrollArea();
    
    ///Ajouts des boutons
    ajouter = new QPushButton("Ajouter un couple");
    //addNotOriented = new QPushButton("Ajouter une relation (NO)");
    Bquit = new QPushButton("Quitter");
    
    ///Connexion des boutons aux slots
    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(addRelation()));
    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(updateRelationManager()));
    //QObject::connect(addNotOriented, SIGNAL(clicked()), this, SLOT(addRelationNotOriented()));
    //QObject::connect(addNotOriented, SIGNAL(clicked()), this, SLOT(updateRelationManager()));
    QObject::connect(Bquit, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(Bquit, SIGNAL(clicked()), this, SLOT(returnToAffichageNote()));
    
    ///Ajout des boutons
    layout->addWidget(listNotesGauche, 0, 0);

    layout->addWidget(listNotesDroite, 0, 2);
    
   QVBoxLayout* layout3=new QVBoxLayout;

    layout3->addWidget(listRelation);

    layout3->addWidget(LineCouple);

    layout3->addWidget(Lab);

    layout->addWidget(ajouter, 1, 1);

    //layout->addWidget(addNotOriented, 2, 1);

    layout->addWidget(Bquit, 1, 2);


    layout->addLayout(layout3,0,1);


    setLayout(layout);

}

///Slot permettant de mettre à jour le widget relationsManager
/*void RelationEditeur::updateRelationManager(){
    MainWindow::getInstance().updateRelationManager();
}*/

///Slot permettant de mettre le Widget dans la partie centrale de l'application
void RelationEditeur::setEmptyCentralWidget(){
    QWidget* empty = new QWidget;
    MainWindow::getInstance().setCentralWidget(empty);
}


void RelationEditeur::returnToAffichageNote(){
MainWindow::getInstance().setCentralWidget(empty);



}
