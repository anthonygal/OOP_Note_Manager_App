#include "PluriNotes.h"

using namespace TIME;

Note::Note(Note& n){
    ID = n.ID;
    titre = n.titre;
    dateCrea = n.dateCrea;
    horaireCrea = n.horaireCrea;
    dateModif = dateNow();
    horaireModif = horaireNow();
    etat = n.etat;
    actuel = true;
    n.setActuel();
}

void Note::afficher(std::ostream& f) const {
    f<<"\n------ "<<typeid(*this).name()<<" "<<ID<<(actuel?" (Version Actuelle)":" (Ancienne Version)")<<" ------\n";
    f<<"\nTitre : "<<titre;
    f<<"\nCree le : "<<dateCrea<<" a "<<horaireCrea;
    f<<"\nModifie le "<<dateModif<<" a "<<horaireModif;
    f<<"\nEtat : ";
    switch(etat){
        case 0: f<<"Active"; break;
        case 1: f<<"Archivee"; break;
        case 2: f<<"Dans la corbeille"; break;
    }
    affichageSpecifique(f);
    f<<"\n\n-------\n";
}

void Article::affichageSpecifique(std::ostream& f) const {
    f<<"\nTexte : "<<texte;
}

//Appel des constructeur par recopie => sera utilisé lors du design Pattern Factory method plus tard
/*Article* Article::clone(){
    return new Article(*this);
}

Tache* Tache::clone(){
    return new Tache(*this);
}

Multimedia* Multimedia::clone(){
    return new Multimedia(*this);
}*/
