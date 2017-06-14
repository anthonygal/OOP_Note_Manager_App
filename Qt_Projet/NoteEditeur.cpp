#include "NoteEditeur.h"
#include "FenetrePrincipale.h"
#include "Manager.h"
#include "Notes.h"

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

ArticleEditeur::ArticleEditeur(Article& a, QWidget* parent) : NoteEditeur(a,parent), article(a)
{
    texteLayout = new QHBoxLayout;
        texteLab = new QLabel("Texte", this);
        texte = new QTextEdit(this);
            texte->setText(article.getTexte());
        texteLayout->addWidget(texteLab);
        texteLayout->addWidget(texte);

    layer->addLayout(texteLayout);
//    layer->addWidget(enregistrer);
//    layer->addWidget(annuler);
    layer->addLayout(boutonLayout);
    setLayout(layer);

    QObject::connect(texte, SIGNAL(textChanged()), this, SLOT(activerEnregistrer()));
    QObject::connect(titre, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(enregistrer,SIGNAL(clicked()),this, SLOT(enregistrerNote()));
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(quit()));
}


TacheEditeur::TacheEditeur(Tache& t, QWidget* parent) : NoteEditeur(t,parent), tache(t)
{
    actionLayout = new QHBoxLayout;
        actionLab =new QLabel ("Action",this);
        action= new QTextEdit(this);  action->setText(tache.getAction());
    actionLayout->addWidget(actionLab);
    actionLayout->addWidget(action);

    statutLayout = new QHBoxLayout;
        statutLab = new QLabel ("Statut",this);
        statut = new QLineEdit(this); statut->setText(tache.TacheStatuttoQString());
    statutLayout->addWidget(statutLab);
    statutLayout->addWidget(statut);

    prioriteLayout = new QHBoxLayout;
        prioriteLab = new QLabel ("Priorite", this);
        priorite = new QSpinBox(this); priorite->setValue(tache.getPriorite()); priorite->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    prioriteLayout->addWidget(prioriteLab);
    prioriteLayout->addWidget(priorite);

    echeanceLayout = new QHBoxLayout;
        echeanceLab = new QLabel ("Echeance", this);
        echeance =new QCalendarWidget(this); echeance->setSelectedDate(tache.getEcheance());
    echeanceLayout->addWidget(echeanceLab);
    echeanceLayout->addWidget(echeance);

    layer->addLayout(actionLayout);
    layer->addLayout(statutLayout);
    layer->addLayout(prioriteLayout);
    layer->addLayout(echeanceLayout);
    layer->addLayout(boutonLayout);

    setLayout(layer);

    QObject::connect(titre, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(statut, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(priorite, SIGNAL(valueChanged(int)), this, SLOT(activerEnregistrer()));
    QObject::connect(action, SIGNAL(textChanged()), this, SLOT(activerEnregistrer()));
    QObject::connect(echeance, SIGNAL(selectionChanged()), this, SLOT(activerEnregistrer()));
    QObject::connect(enregistrer,SIGNAL(clicked()),this, SLOT(enregistrerNote()));
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(quit()));
}


MultimediaEditeur::MultimediaEditeur(Multimedia& m, QWidget* parent) : NoteEditeur(m,parent), multimedia(m) {

    descLab =new QLabel ("Description",this);
    desc= new QTextEdit(this);

    //typeLab = new QLabel ("Type",this);
    type = new QGroupBox("Type de Multimedia", this);

    adresseLab = new QLabel ("Adresse Fichier",this);
    adresse= new QLineEdit(this);    

    Image = new QRadioButton("Image");
    Audio = new QRadioButton("Audio");
    Video = new QRadioButton("Video");

    desc->setText(multimedia.getDescription());

    if(multimedia.getType()==image) Image->setChecked(true);
    else if (multimedia.getType()==audio) Audio->setChecked(true);
           else Video->setChecked(true);

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

    hbox = new QHBoxLayout;
    hbox->addWidget(Image);
    hbox->addWidget(Audio);
    hbox->addWidget(Video);
    type->setLayout(hbox);

    layer->addLayout(descLayout);
    layer->addLayout(typeLayout);
    layer->addLayout(adresseLayout);

    layer->addLayout(boutonLayout);

    setLayout(layer);

    QObject::connect(titre, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(adresse, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer));
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(activerEnregistrer));
    QObject::connect(type, SIGNAL(), this, SLOT(activerEnregistrer));
    QObject::connect(enregistrer,SIGNAL(clicked()),this, SLOT(enregistrerNote()));
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(quit()));
}

void ArticleEditeur::enregistrerNote(){
    Manager& m=Manager::donneInstance();
    for(Relation::IteratorCouples itc=m.getReference().getIteratorCouples();!itc.isDone();itc.next())
        if(itc.current().getID1()==article.getID())
            m.getReference().supprimerCouple(itc.current());
    Article* a = new Article(article);
    a->setTitre(titre->text());
    a->setTexte(texte->toPlainText());   
    m.ajouterNote(*a);
    QMessageBox::information(this,"Sauvegarde","Votre Article a bien été enregistré");
    close();
}

void TacheEditeur::enregistrerNote(){
    Manager& m=Manager::donneInstance();
    for(Relation::IteratorCouples itc=m.getReference().getIteratorCouples();!itc.isDone();itc.next())
        if(itc.current().getID1()==tache.getID())
            m.getReference().supprimerCouple(itc.current());
    Tache* t = new Tache(tache);
    t->setTitre(titre->text());
    t->setAction(action->toPlainText());
    t->setEcheance(echeance->selectedDate());
    t->setPriorite(priorite->value());
    m.ajouterNote(*t);
    QMessageBox::information(this,"Sauvegarde","Votre Tache a bien été enregistrée");
    close();
}

void MultimediaEditeur::enregistrerNote(){
    Manager& ma = Manager::donneInstance();
    for(Relation::IteratorCouples itc=ma.getReference().getIteratorCouples();!itc.isDone();itc.next())
        if(itc.current().getID1()==multimedia.getID())
            ma.getReference().supprimerCouple(itc.current());
    Multimedia* m = new Multimedia(multimedia);
    m->setTitre(titre->text());
    m->setDescription(desc->toPlainText());
    m->setAdresseFichier(adresse->text());
    if(Image->isChecked()) m->setType(image);
    else if(Audio->isChecked()) m->setType(audio);
    else m->setType(video);
    ma.ajouterNote(*m);
    QMessageBox::information(this,"Sauvegarde","Votre Multimedia a bien été enregistré");
    close();
}

void NoteEditeur::activerEnregistrer() {
    enregistrer->setEnabled(true);
    //isSaved=false;
}
