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

Note::Note(const Note& n){
    ID = n.ID;
    titre = n.titre;
    dateCrea = n.dateCrea;
    horaireCrea = n.horaireCrea;
    dateModif = n.dateModif;
    horaireModif = n.horaireModif;
    etat = n.etat;
    actuel = n.actuel;
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


void Manager::Affichertout()const{
for(Manager::IteratorNotes it=begin();it!=Manager::end();++it ){
    std::cout<<*it;
}
}


std::ostream& operator<<(std::ostream& f, const Note& n) {
        n.afficher(f);
        return f;}


 Manager& Manager::operator<<(Note& n){
    if (Manager::nbNotes==Manager::nbNotesMax){
        Note** newtab= new Note* [Manager::nbNotesMax+5];
        for(int i=0; i=Manager::nbNotes;i++){
            newtab[i]=Manager::notes[i];
        }
    Note** oldtab= Manager::notes;
    notes=newtab;
    delete [] oldtab;
    }
    Manager::notes[Manager::nbNotes+1]=n.clone();
    Manager::nbNotes=Manager::nbNotes+1;
    return *this;
    };

//Appel des constructeur par recopie => sera utilisé lors du design Pattern Factory method plus tard
Article* Article::clone()const{
 Article* a=new Article(*this);
    return a;
}

/*
Tache* Tache::clone()const{
    return new Tache(*this);
}

Multimedia* Multimedia::clone()const{
    return new Multimedia(*this);
}*/
