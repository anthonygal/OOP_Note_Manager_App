#include "NewNote.h"
#include "Manager.h"
#include "FenetrePrincipale.h"

NewNote::NewNote(QWidget *parent) : QWidget(parent){
    layer = new QVBoxLayout;

        titreLayout = new QHBoxLayout;
            titreLab = new  QLabel("Titre :");
            titre = new QLineEdit;
        titreLayout->addWidget(titreLab);
        titreLayout->addWidget(titre);

        boutonLayout = new QHBoxLayout;
            enregistrer = new QPushButton("Enregistrer");
            annuler = new QPushButton("Annuler");
        boutonLayout->addWidget(enregistrer);
        boutonLayout->addWidget(annuler);
        boutonLayout->setAlignment(Qt::AlignHCenter);

    layer->addLayout(titreLayout);

    QObject::connect(enregistrer,SIGNAL(clicked()),this, SLOT(enregistrerNote()));
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
}

NewArticle::NewArticle(QWidget *parent) : NewNote(parent)
{
    texteLayout = new QHBoxLayout;
        texteLab = new QLabel("Texte");
        texte = new QTextEdit;
    texteLayout->addWidget(texteLab);
    texteLayout->addWidget(texte);

    layer->addLayout(texteLayout);
    layer->addLayout(boutonLayout);
    setLayout(layer);
}

NewTache::NewTache(QWidget *parent) : NewNote(parent)
{
    actionLayout = new QHBoxLayout;
        actionLab =new QLabel ("Action");
        action= new QTextEdit;
    actionLayout->addWidget(actionLab);
    actionLayout->addWidget(action);

    prioriteLayout = new QHBoxLayout;
        prioriteLab = new QLabel ("Priorite");
        priorite = new QSpinBox;
    prioriteLayout->addWidget(prioriteLab);
    prioriteLayout->addWidget(priorite);

    echeanceLayout = new QHBoxLayout;
        echeanceLab = new QLabel ("Echeance");
        echeance =new QCalendarWidget;
    echeanceLayout->addWidget(echeanceLab);
    echeanceLayout->addWidget(echeance);

    layer->addLayout(actionLayout);
    layer->addLayout(prioriteLayout);
    layer->addLayout(echeanceLayout);
    layer->addLayout(boutonLayout);

    setLayout(layer);
}

NewMultimedia::NewMultimedia(QWidget *parent) : NewNote(parent)
{
    descLayout = new QHBoxLayout;
        descLab = new QLabel ("Description");
        desc = new QTextEdit;
    descLayout->addWidget(descLab);
    descLayout->addWidget(desc);

    type = new QGroupBox("Type de Multimedia");
    hbox = new QHBoxLayout;
        Image = new QRadioButton("Image"); Image->setChecked(true);
        Audio = new QRadioButton("Audio");
        Video = new QRadioButton("Video");
    hbox->addWidget(Image);
    hbox->addWidget(Audio);
    hbox->addWidget(Video);
    type->setLayout(hbox);

    adresseLayout = new QHBoxLayout;
        adresseLab = new QLabel ("Adresse Fichier");
        adresse = new QLabel("Aucun fichier selectionné");
        parcourir = new QPushButton("Parcourir");
    adresseLayout->addWidget(adresseLab);
    adresseLayout->addWidget(adresse);

    layer->addLayout(descLayout);
    layer->addWidget(type);
    layer->addLayout(adresseLayout);
    layer->addLayout(boutonLayout);

    setLayout(layer);

    QObject::connect(parcourir,SIGNAL(clicked()),this,SLOT(modifierAdresse()));
}

void NewMultimedia::modifierAdresse(){
    adresse->setText(QFileDialog::getOpenFileName());
}

void NewArticle::enregistrerNote(){
    try{
        Note& n = Manager::donneInstance().newArticle(titre->text(),texte->toPlainText());
        FenetrePrincipale::donneInstance().updateFenetre(n);
        close();
    }catch(NoteException e){QMessageBox::critical(this,"Erreur",e.getInfo());}
}

void NewTache::enregistrerNote(){
    try{
        Note& n = Manager::donneInstance().newTache(titre->text(),action->toPlainText(),priorite->value(),echeance->selectedDate());
        FenetrePrincipale::donneInstance().updateFenetre(n);
        close();
    }catch(NoteException e){QMessageBox::critical(this,"Erreur",e.getInfo());}
}

void NewMultimedia::enregistrerNote(){
    try{
        if(Video->isChecked()){
            Note& n = Manager::donneInstance().newMultimedia(titre->text(),adresse->text(),desc->toPlainText(),video);
            FenetrePrincipale::donneInstance().updateFenetre(n);
        }
        else if(Audio->isChecked()){
            Note& n = Manager::donneInstance().newMultimedia(titre->text(),adresse->text(),desc->toPlainText(),audio);
            FenetrePrincipale::donneInstance().updateFenetre(n);
        }
        else{
            Note& n = Manager::donneInstance().newMultimedia(titre->text(),adresse->text(),desc->toPlainText(),image);
            FenetrePrincipale::donneInstance().updateFenetre(n);
        }
        close();
    }catch(NoteException e){QMessageBox::critical(this,"Erreur",e.getInfo());}
}
