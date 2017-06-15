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
    unsigned long n1 = Manager::donneInstance().getIDNoteWithTitre(titre1);
    
    ///On récupère la note n2 dans le QlistWidget listNotesRight
    QListWidgetItem* selectedItem2 = listNotesDroite->currentItem();
    QString titre2 = selectedItem2->text();
    unsigned long n2= Manager::donneInstance().getIDNoteWithTitre(titre2);
    
     QListWidgetItem* selectedItem3 = listRelation->currentItem();
     QString titre3 = selectedItem3->text();
     Relation& r=Manager::donneInstance().getRelation(titre3);

     QString Label = LineCouple->text();

     r.addCouple(n1, n2, Label);
    
    
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
    Bquit = new QPushButton("Quitter");
    
    ///Connexion des boutons aux slots
    listNotesDroite->setEnabled(false);
    listNotesGauche->setEnabled(false);
    LineCouple->setEnabled(false);
    ajouter->setEnabled(false);//LineCouple->textEdited(QString)&&

    QObject::connect(listRelation, SIGNAL(itemSelectionChanged()),this , SLOT(activerlistNotesGauche()));
    QObject::connect(listNotesGauche, SIGNAL(itemSelectionChanged()), this, SLOT(activerlistNotesDroite()));
    QObject::connect(listNotesDroite, SIGNAL(itemSelectionChanged()), this, SLOT(activerLineCouple()));
    QObject::connect(LineCouple, SIGNAL(textChanged(QString)), this, SLOT(activerajouter()));
    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(addCouple()));
    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(returnToAffichageNote()));
    QObject::connect(Bquit, SIGNAL(clicked()), this, SLOT(returnToAffichageNote()));
    
    ///Ajout des boutons
    layout->addWidget(listNotesGauche, 0, 0);

    layout->addWidget(listNotesDroite, 0, 2);
    
   QVBoxLayout* layout3=new QVBoxLayout;

    layout3->addWidget(listRelation);

    layout3->addWidget(LineCouple);

    layout3->addWidget(Lab);

    layout->addWidget(ajouter, 1, 1);

    layout->addWidget(Bquit, 1, 2);


    layout->addLayout(layout3,0,1);


    setLayout(layout);

}

///Slot permettant de mettre à jour le widget relationsManager
/*void RelationEditeur::updateRelationManager(){
    MainWindow::getInstance().updateRelationManager();
}*/
/*
///Slot permettant de mettre le Widget dans la partie centrale de l'application
void RelationEditeur::setEmptyCentralWidget(){
    QWidget* empty = new QWidget;
    MainWindow::getInstance().setCentralWidget(empty);
}
*/

void RelationEditeur::returnToAffichageNote(){
    FenetrePrincipale& fp= FenetrePrincipale::donneInstance();
    fp.reaffichageNote();

}

void RelationEditeur::activerlistNotesDroite(){
    listNotesDroite->setEnabled(true);
}

void RelationEditeur::activerlistNotesGauche(){
    listNotesGauche->setEnabled(true);
}

void RelationEditeur::activerLineCouple(){
    LineCouple->setEnabled(true);
}

void RelationEditeur::activerajouter(){
    ajouter->setEnabled(true);
}

RelationCreateur::RelationCreateur(QWidget* parent){
    titre=new QLineEdit();
    Labtitre= new QLabel("Titre : ");
    Labdescription= new QLabel("Description : ");
    description= new QTextEdit();
    orientee= new QCheckBox("Orientee");
    add = new QPushButton("Ajouter une relation");
    quit = new QPushButton("Quitter");

    QHBoxLayout* layout1 = new QHBoxLayout();

    QHBoxLayout* layout2 = new QHBoxLayout();

    layout1->addWidget(Labtitre);
    layout1->addWidget(titre);

    layout2->addWidget(Labdescription);
    layout2->addWidget(description);

    layout3 = new QVBoxLayout();

    layout3->addLayout(layout1);
    layout3->addLayout(layout2);
    layout3->addWidget(orientee);
    layout3->addWidget(add);
    layout3->addWidget(quit);

     add->setEnabled(false);
     QObject::connect(titre, SIGNAL(textEdited(QString)),this , SLOT(activerAdd()));
     QObject::connect(add, SIGNAL(clicked()), this, SLOT(addRelation()));
     QObject::connect(quit, SIGNAL(clicked()), this, SLOT(close()));
     setLayout(layout3);

}

void RelationCreateur::activerAdd(){
    add->setEnabled(true);
}

void RelationCreateur::addRelation(){
    Manager& m= Manager::donneInstance();
    QString tit = titre->text();
    QString de = description->toPlainText();
    bool o;
    if(orientee->isChecked())
    {o=true;}
    else  {o=false;}
    m.addRelation(tit, de, o);
    QMessageBox::information(this, "Succès", "Le relation a bien été créée");
    this->close();

}
