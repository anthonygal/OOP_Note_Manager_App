#include "QNotes.h"

QNote::QNote(Note& n, QWidget *parent) : QWidget(parent), note(n){
    QLabel *TypeNote = new QLabel(n.getTypeNote()); TypeNote->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *Actuelle = new QLabel(n.isActuelle()?"(Version Actuelle)":"(Ancienne Version)");
    QLabel *lID = new QLabel("ID : ");
    QLabel *ID = new QLabel(QString::number(n.getID()));
    QLabel *lEtat = new QLabel("Etat : ");
    QLabel *Etat = new QLabel(n.NoteEtattoQString());
    QLabel *lTitre = new QLabel("Titre : ");
    QLabel *Titre = new QLabel(n.getTitre());
    QLabel *lDateCrea = new QLabel("Date de création : ");
    QLabel *DateCrea = new QLabel(n.getDateCrea().toString(formatDateTime));
    QLabel *lDateModif = new QLabel("Date de modification : ");
    QLabel *DateModif = new QLabel(n.getDateModif().toString(formatDateTime));

    QHBoxLayout *hlayout0 = new QHBoxLayout;
        hlayout0->addWidget(TypeNote);
        hlayout0->addWidget(Actuelle);
    QHBoxLayout *hlayout1 = new QHBoxLayout;
        hlayout1->addWidget(lID);
        hlayout1->addWidget(ID);
    QHBoxLayout *hlayout2 = new QHBoxLayout;
        hlayout2->addWidget(lEtat);
        hlayout2->addWidget(Etat);
    QHBoxLayout *hlayout3 = new QHBoxLayout;
        hlayout3->addWidget(lTitre);
        hlayout3->addWidget(Titre);
    QHBoxLayout *hlayout4 = new QHBoxLayout;
        hlayout4->addWidget(lDateCrea);
        hlayout4->addWidget(DateCrea);
    QHBoxLayout *hlayout5 = new QHBoxLayout;
        hlayout5->addWidget(lDateModif);
        hlayout5->addWidget(DateModif);

    QVBoxLayout *noteLayout = new QVBoxLayout;
        noteLayout->addLayout(hlayout0);
        noteLayout->addLayout(hlayout1);
        noteLayout->addLayout(hlayout2);
        noteLayout->addLayout(hlayout3);
        noteLayout->addLayout(hlayout4);
        noteLayout->addLayout(hlayout5);

    partieNote = noteLayout;
    setLayout(noteLayout);
}

//QArticle::QArticle(Article& a, QWidget *parent): QNote(a){

//}
