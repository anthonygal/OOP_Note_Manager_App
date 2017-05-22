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

void Note::afficher() const {
    std::cout<<"\n\n****** Note "<<ID<<(actuel?" (Version Actuelle)":" (Ancienne Version)")<<" ******\n";
    std::cout<<"\nTitre : "<<titre;
    std::cout<<"\nCree le : "<<dateCrea<<" a "<<horaireCrea;
    std::cout<<"\nModifie le "<<dateModif<<" a "<<horaireModif;
    std::cout<<"\nEtat : ";
    switch(etat){
        case 0: std::cout<<"Active"; break;
        case 1: std::cout<<"Archivee"; break;
        case 2: std::cout<<"Dans la corbeille"; break;
    }
    std::cout<<"\n\n************\n";
}

//Appel des constructeur par recopie => sera utilisé lors du design Pattern Factory method plus tard
Article* Article::clone(){
    return new Article(*this);
}

Tache* Tache::clone(){
    return new Tache(*this);
}

Multimedia* Multimedia::clone(){
    return new Multimedia(*this);
}
