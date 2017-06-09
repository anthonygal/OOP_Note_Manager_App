#include "NoteEditeur.h"
#include "FenetrePrincipale.h"
#include "Manager.h"

NoteEditeur::NoteEditeur(Note& n, QWidget* parent)
{
    IDLab= new QLabel("ID :", this);
    titreLab = new  QLabel("Titre :", this);
    dateCreaLab = new QLabel("Date de création :", this);
    dateModifLab = new QLabel("Date de Modification :", this);

    ID = new QLineEdit(this);
    titre = new QLineEdit(this);
    dateCrea = new QDateEdit(this);
    dateModif =  new QDateEdit(this);

    enregistrer = new QPushButton("Enregistrer",this);
    annuler = new QPushButton("Annuler",this);

    IDLayout = new QHBoxLayout;
    titreLayout = new QHBoxLayout;
    datesLayout = new QHBoxLayout;
    boutonLayout = new QHBoxLayout;

    layer = new QVBoxLayout;

    ID->setText(QString::number(n.getID()));
    dateCrea->setDateTime(n.getDateCrea());
    dateModif->setDateTime(n.getDateModif());
    titre->setText(n.getTitre());

    IDLayout->addWidget(IDLab);
    IDLayout->addWidget(ID);
    titreLayout->addWidget(titreLab);
    titreLayout->addWidget(titre);
    datesLayout->addWidget(dateCreaLab);
    datesLayout->addWidget(dateCrea);
    datesLayout->addWidget(dateModif);
    datesLayout->addWidget(dateModif);


    boutonLayout->addWidget(enregistrer);
    boutonLayout->addWidget(annuler);
    boutonLayout->setAlignment(Qt::AlignHCenter);


    layer->addLayout(IDLayout);
    layer->addLayout(titreLayout);
    layer->addLayout(datesLayout);

    ID->setDisabled(true);
    dateCrea->setDisabled(true);
    dateModif->setDisabled(true);

}

ArticleEditeur::ArticleEditeur(Article& a, QWidget* parent) : NoteEditeur(a,parent), article(a) {
      texteLab = new QLabel("Texte", this);
      texte = new QTextEdit(this);

      texte->setText(article.getTexte());

      texteLayout = new QHBoxLayout;

      texteLayout->addWidget(texteLab);
      texteLayout->addWidget(texte);

      texteLayout->addWidget(texte);

      layer->addLayout(texteLayout);

      layer->addWidget(enregistrer);
      layer->addWidget(annuler);
      layer->addLayout(boutonLayout);

      setLayout(layer);

      QObject::connect(enregistrer,SIGNAL(clicked()),this, SLOT(enregistrerNote()));

      QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(quit()));
      QObject::connect(texte, SIGNAL(textChanged()), this, SLOT(activerEnregistrer()));
      QObject::connect(titre, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
}


TacheEditeur::TacheEditeur(Tache& t, QWidget* parent) : NoteEditeur(t,parent), tache(t) {
    actionLab =new QLabel ("Action",this);
    action= new QTextEdit(this);

    statutLab = new QLabel ("Statut",this);
    statut = new QLineEdit(this);

    echeanceLab = new QLabel ("Echeance", this);
    echeance =new QCalendarWidget(this);

    prioriteLab = new QLabel ("Priorite", this);
    priorite = new QSpinBox(this);

    action->setText(tache.getAction());
    statut->setText(tache.TacheStatuttoQString());
    priorite->setValue(tache.getPriorite()); priorite->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    echeance->setSelectedDate(tache.getEcheance());

    actionLayout = new QHBoxLayout;
    statutLayout = new QHBoxLayout;
    prioriteLayout = new QHBoxLayout;
    echeanceLayout = new QHBoxLayout;

    actionLayout->addWidget(actionLab);
    actionLayout->addWidget(action);
    statutLayout->addWidget(statutLab);
    statutLayout->addWidget(statut);
    prioriteLayout->addWidget(prioriteLab);
    prioriteLayout->addWidget(priorite);
    echeanceLayout->addWidget(echeanceLab);
    echeanceLayout->addWidget(echeance);

    layer->addLayout(actionLayout);
    layer->addLayout(statutLayout);
    layer->addLayout(prioriteLayout);
    layer->addLayout(echeanceLayout);
    layer->addLayout(boutonLayout);

    setLayout(layer);

    QObject::connect(enregistrer,SIGNAL(clicked()),this, SLOT(enregistrerNote()));

    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(quit()));

    QObject::connect(titre, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(statut, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(priorite, SIGNAL(valueChanged(int)), this, SLOT(activerEnregistrer()));
    QObject::connect(action, SIGNAL(textChanged()), this, SLOT(activerEnregistrer()));
    QObject::connect(echeance, SIGNAL(selectionChanged()), this, SLOT(activerEnregistrer()));
}


MultimediaEditeur::MultimediaEditeur(Multimedia& m, QWidget* parent) : NoteEditeur(m,parent), multimedia(m) {

    descLab =new QLabel ("Description",this);
    desc= new QTextEdit(this);

    typeLab = new QLabel ("Type",this);
    type = new QLineEdit(this);

    adresseLab = new QLabel ("Adresse Fichier",this);
    adresse= new QLineEdit(this);


    /*
    desc = new QTextEdit(this);
    filename = new QLineEdit(this);
    type = new QGroupBox("type de Multimedia", this);

    QRadioButton *Image = new QRadioButton("Image");
    QRadioButton *Audio = new QRadioButton("Audio");
    QRadioButton *Video = new QRadioButton("Video");

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(Image);
    hbox->addWidget(Audio);
    hbox->addWidget(Video);*/

    desc->setText(multimedia.getDescription());
    type->setText(multimedia.TypeMultimediatoQString());
    adresse->setText(multimedia.getAdresseFichier());


    descLayout = new QHBoxLayout;
    typeLayout = new QHBoxLayout;
    adresseLayout = new QHBoxLayout;

    descLayout->addWidget(descLab);
    descLayout->addWidget(desc);
    typeLayout->addWidget(typeLab);
    typeLayout->addWidget(type);
    adresseLayout->addWidget(adresseLab);
    adresseLayout->addWidget(adresse);

    layer->addLayout(descLayout);
    layer->addLayout(typeLayout);
    layer->addLayout(adresseLayout);

    layer->addLayout(boutonLayout);

    setLayout(layer);

    QObject::connect(enregistrer,SIGNAL(clicked()),this, SLOT(enregistrerNote()));

    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(quit()));
    QObject::connect(titre, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(adresse, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer));
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(activerEnregistrer));
    QObject::connect(type, SIGNAL(), this, SLOT(activerEnregistrer));
}

void ArticleEditeur::enregistrerNote(){
    Article* a = new Article(article);
    a->setTitre(titre->text());
    a->setTexte(texte->toPlainText());
    Manager& m=Manager::donneInstance();
    m.ajouterNote(*a);
    QMessageBox::information(this,"Sauvegarde","Votre Article a bien été enregistré");
    close();
}

void TacheEditeur::enregistrerNote(){
    Tache* t = new Tache(tache);
    t->setTitre(titre->text());
    t->setAction(action->toPlainText());
    t->setEcheance(echeance->selectedDate());
    t->setPriorite(priorite->value());
    Manager& m=Manager::donneInstance();
    m.ajouterNote(*t);
    QMessageBox::information(this,"Sauvegarde","Votre Tache a bien été enregistrée");
    close();
}

void MultimediaEditeur::enregistrerNote(){
    Multimedia* m = new Multimedia(multimedia);
    m->setTitre(titre->text());
    m->setDescription(desc->toPlainText());
    m->setAdresseFichier(adresse->text());
    m->setType(m->QStringtoTypeMultimedia(type->text()));
    Manager& ma = Manager::donneInstance();
    ma.ajouterNote(*m);
    QMessageBox::information(this,"Sauvegarde","Votre Multimedia a bien été enregistré");
    close();
}

void NoteEditeur::activerEnregistrer() {
    enregistrer->setEnabled(true);
    //isSaved=false;
}
