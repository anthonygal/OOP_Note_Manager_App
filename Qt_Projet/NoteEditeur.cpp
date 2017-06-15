#include "NoteEditeur.h"
#include "FenetrePrincipale.h"
#include "Manager.h"
#include "Notes.h"

NoteEditeur::NoteEditeur(Note& n, QWidget* parent):QWidget(parent), note(n)
{
    layer = new QVBoxLayout;
        IDLayout = new QHBoxLayout;
            IDLab= new QLabel("ID :");
            ID = new QLineEdit(QString::number(n.getID())); ID->setDisabled(true);
        titreLayout = new QHBoxLayout;
            titreLab = new  QLabel("Titre :");
            titre = new QLineEdit(n.getTitre());
        datesLayout = new QHBoxLayout;
            dateCreaLab = new QLabel("Date de création :");
            dateCrea = new QDateTimeEdit(n.getDateCrea()); dateCrea->setDisabled(true);
            dateModifLab = new QLabel("Date de Modification :");
            dateModif =  new QDateTimeEdit(n.getDateModif()); dateModif->setDisabled(true);
        boutonLayout = new QHBoxLayout;
            enregistrer = new QPushButton("Enregistrer"); enregistrer->setEnabled(false);
            annuler = new QPushButton("Annuler");

    IDLayout->addWidget(IDLab);
    IDLayout->addWidget(ID);
    titreLayout->addWidget(titreLab);
    titreLayout->addWidget(titre);
    datesLayout->addWidget(dateCreaLab);
    datesLayout->addWidget(dateCrea);
    datesLayout->addWidget(dateModifLab);
    datesLayout->addWidget(dateModif);

    boutonLayout->addWidget(enregistrer);
    boutonLayout->addWidget(annuler);
    boutonLayout->setAlignment(Qt::AlignHCenter);

    layer->addLayout(IDLayout);
    layer->addLayout(titreLayout);
    layer->addLayout(datesLayout);

    QObject::connect(titre, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(enregistrer,SIGNAL(clicked()),this, SLOT(enregistrerNote()));
    QObject::connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
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
    layer->addLayout(boutonLayout);
    setLayout(layer);

    QObject::connect(texte, SIGNAL(textChanged()), this, SLOT(activerEnregistrer()));
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

    QObject::connect(statut, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(priorite, SIGNAL(valueChanged(int)), this, SLOT(activerEnregistrer()));
    QObject::connect(action, SIGNAL(textChanged()), this, SLOT(activerEnregistrer()));
    QObject::connect(echeance, SIGNAL(selectionChanged()), this, SLOT(activerEnregistrer()));
}


MultimediaEditeur::MultimediaEditeur(Multimedia& m, QWidget* parent) : NoteEditeur(m,parent), multimedia(m) {

    descLab =new QLabel ("Description",this);
    desc= new QTextEdit(this); desc->setText(multimedia.getDescription());

    type = new QGroupBox("Type de Multimedia", this);
        Image = new QRadioButton("Image");
        Audio = new QRadioButton("Audio");
        Video = new QRadioButton("Video");

        if(multimedia.getType()==image) Image->setChecked(true);
        else if (multimedia.getType()==audio) Audio->setChecked(true);
        else Video->setChecked(true);

        hbox = new QHBoxLayout;
        hbox->addWidget(Image);
        hbox->addWidget(Audio);
        hbox->addWidget(Video);
    type->setLayout(hbox);

    adresseLab = new QLabel ("Adresse Fichier",this);
    adresse= new QLineEdit(this); adresse->setText(multimedia.getAdresseFichier());

    descLayout = new QHBoxLayout;
    typeLayout = new QHBoxLayout;
    adresseLayout = new QHBoxLayout;

    descLayout->addWidget(descLab);
    descLayout->addWidget(desc);
    typeLayout->addWidget(type);
    adresseLayout->addWidget(adresseLab);
    adresseLayout->addWidget(adresse);

    layer->addLayout(descLayout);
    layer->addLayout(typeLayout);
    layer->addLayout(adresseLayout);
    layer->addLayout(boutonLayout);

    setLayout(layer);


    QObject::connect(adresse, SIGNAL(textEdited(QString)), this, SLOT(activerEnregistrer()));
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(activerEnregistrer()));
    QObject::connect(Image, SIGNAL(clicked()), this, SLOT(activerEnregistrer()));
    QObject::connect(Audio, SIGNAL(clicked()), this, SLOT(activerEnregistrer()));
    QObject::connect(Video, SIGNAL(clicked()), this, SLOT(activerEnregistrer()));
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
    FenetrePrincipale::donneInstance().updateFenetre(*a);
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
    FenetrePrincipale::donneInstance().updateFenetre(*t);
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
    FenetrePrincipale::donneInstance().updateFenetre(*m);
}

void NoteEditeur::activerEnregistrer() {
    enregistrer->setEnabled(true);
}
