#include "QNotes.h"

QNoteReduite::QNoteReduite(Note& n, FenetrePrincipale* f, QWidget* parent) : QPushButton(parent), note(n), fenetre(f)
{
    setMinimumSize(275,40);
    QHBoxLayout *layout = new QHBoxLayout;
        QLabel *Type = new QLabel(n.getTypeNote());
        QLabel *ID = new QLabel(QString::number(n.getID()));
        QLabel *Titre = new QLabel(n.getTitre());
        QLabel *DateModif = new QLabel(n.getDateModif().toString(formatDateTime));
        layout->addWidget(Type);
        layout->addWidget(ID);
        layout->addWidget(Titre);
        layout->addWidget(DateModif);
    setLayout(layout);
    QObject::connect(this,SIGNAL(clicked()),SLOT(onClicked()));
}

void QNoteReduite::onClicked(){
    fenetre->changerNotePrincipale(note);
}

QNote::QNote(Note& n, QWidget *parent) : QWidget(parent), note(n)
{
    QVBoxLayout *vlayout = new QVBoxLayout;

    QHBoxLayout *hlayout0 = new QHBoxLayout;
        QLabel *TypeNote = new QLabel(n.getTypeNote()); TypeNote->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        QLabel *Actuelle = new QLabel(n.isActuelle()?"(Version Actuelle)":"(Ancienne Version)",this);
        hlayout0->addWidget(TypeNote);
        hlayout0->addWidget(Actuelle);
    vlayout->addLayout(hlayout0);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
        QLabel *lID = new QLabel("ID : ");
        QLabel *ID = new QLabel(QString::number(n.getID()));
        hlayout1->addWidget(lID);
        hlayout1->addWidget(ID);
    vlayout->addLayout(hlayout1);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
        QLabel *lEtat = new QLabel("Etat : ");
        QLabel *Etat = new QLabel(n.NoteEtattoQString());
        hlayout2->addWidget(lEtat);
        hlayout2->addWidget(Etat);
    vlayout->addLayout(hlayout2);

    QHBoxLayout *hlayout3 = new QHBoxLayout;
        QLabel *lDateCrea = new QLabel("Date de création : ");
        QLabel *DateCrea = new QLabel(n.getDateCrea().toString(formatDateTime));
        hlayout3->addWidget(lDateCrea);
        hlayout3->addWidget(DateCrea);
    vlayout->addLayout(hlayout3);

    QHBoxLayout *hlayout4 = new QHBoxLayout;
        QLabel *lDateModif = new QLabel("Date de modification : ");
        QLabel *DateModif = new QLabel(n.getDateModif().toString(formatDateTime));
        hlayout4->addWidget(lDateModif);
        hlayout4->addWidget(DateModif);
    vlayout->addLayout(hlayout4);

    QHBoxLayout *hlayout5 = new QHBoxLayout;
        QLabel *lTitre = new QLabel("Titre : ");
        QLabel *Titre = new QLabel(n.getTitre());
        hlayout5->addWidget(lTitre);
        hlayout5->addWidget(Titre);
    vlayout->addLayout(hlayout5);

    QHBoxLayout *boutonsLayout = new QHBoxLayout;

    if(n.getTypeNote() == "Article"){
        Article& a = dynamic_cast<Article&>(n);

        QHBoxLayout *hlayout6 = new QHBoxLayout;
            QLabel *lTexte = new QLabel("Texte : ");
            QLabel *Texte = new QLabel(a.getTexte());
            hlayout6->addWidget(lTexte);
            hlayout6->addWidget(Texte);
        vlayout->addLayout(hlayout6);
    }

    else if(n.getTypeNote() == "Tache"){
        Tache& t = dynamic_cast<Tache&>(n);

        QHBoxLayout *hlayout6 = new QHBoxLayout;
            QLabel *lStatut = new QLabel("Statut : ");
            QLabel *Statut = new QLabel(t.TacheStatuttoQString());
            hlayout6->addWidget(lStatut);
            hlayout6->addWidget(Statut);
        vlayout->addLayout(hlayout6);

        QHBoxLayout *hlayout7 = new QHBoxLayout;
            QLabel *lAction = new QLabel("Action : ");
            QLabel *Action = new QLabel(t.getAction());
            hlayout7->addWidget(lAction);
            hlayout7->addWidget(Action);
        vlayout->addLayout(hlayout7);

        if(t.getPriorite()){
            QHBoxLayout *hlayout8 = new QHBoxLayout;
                QLabel *lPriorite = new QLabel("Priorite : ");
                QLabel *Priorite = new QLabel(QString::number(t.getPriorite()));
                hlayout8->addWidget(lPriorite);
                hlayout8->addWidget(Priorite);
            vlayout->addLayout(hlayout8);
        }

        if(!t.getEcheance().isNull()){
            QHBoxLayout *hlayout9 = new QHBoxLayout;
                QLabel *lEcheance = new QLabel("Date d'echeance : ");
                QLabel *Echeance = new QLabel(t.getEcheance().toString(formatDate));
                hlayout9->addWidget(lEcheance);
                hlayout9->addWidget(Echeance);
            vlayout->addLayout(hlayout9);
        }
    }

    else if(n.getTypeNote() == "Multimedia"){
        Multimedia& m = dynamic_cast<Multimedia&>(n);

        QHBoxLayout *hlayout6 = new QHBoxLayout;
            QLabel *lType = new QLabel("Type de fichier : ");
            QLabel *Type = new QLabel(m.TypeMultimediatoQString());
            hlayout6->addWidget(lType);
            hlayout6->addWidget(Type);
        vlayout->addLayout(hlayout6);

        QHBoxLayout *hlayout7 = new QHBoxLayout;
            QLabel *lFichier = new QLabel("Adresse du fichier : ");
            QLabel *Fichier = new QLabel(m.getAdresseFichier());
            hlayout7->addWidget(lFichier);
            hlayout7->addWidget(Fichier);
        vlayout->addLayout(hlayout7);

        QHBoxLayout *hlayout8 = new QHBoxLayout;
            QLabel *lDescription = new QLabel("Description : ");
            QLabel *Description = new QLabel(m.getDescription());
            hlayout8->addWidget(lDescription);
            hlayout8->addWidget(Description);
        vlayout->addLayout(hlayout8);
    }

    if(n.getEtat() == active){
        if(n.isActuelle()){
            QPushButton *boutonModifier = new QPushButton("Modifier");
            boutonsLayout->addWidget(boutonModifier);
            QPushButton *boutonSupprimer = new QPushButton("Supprimer");
            boutonsLayout->addWidget(boutonSupprimer);
            QObject::connect(boutonModifier,SIGNAL(clicked()),this,SLOT(editer()));
            QObject::connect(boutonModifier,SIGNAL(clicked()),this,SLOT(supprimer()));
        }
        else{
            QPushButton *boutonRestaurerVersion = new QPushButton("Revenir à cette version");
            boutonsLayout->addWidget(boutonRestaurerVersion);
        }
    }
    else{
        QPushButton *boutonRestaurer = new QPushButton("Restaurer");
        boutonsLayout->addWidget(boutonRestaurer);
    }

    vlayout->addLayout(boutonsLayout);
    setLayout(vlayout);
}

void QNote::editer(){
    //Manager::donneInstance().editNote(note);
}

void QNote::supprimer(){
    Manager::donneInstance().supprimerNote(note);
}
