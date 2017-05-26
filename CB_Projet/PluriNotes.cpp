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

void Tache::affichageSpecifique(std::ostream& f) const {
    f<<"\nAction : "<<action;
    f<<"\nStatut : ";
    switch(statut){
        case 0: f<<"Attente"; break;
        case 1: f<<"En cours"; break;
        case 2: f<<"Terminée"; break;}
    if (priorite!=0){
    f<<"\nPriorite : "<<priorite;
    }
    if (echeance.getAnnee()!=0 || echeance.getMois()!=1 ||echeance.getJour()!=1  ){
    f<<"\nEcheance : "<<echeance;
    }

}



void Manager::Affichertout()const{
   // for (unsigned int i=0; i<Manager::nbNotes-1; i++)
   // {
      // Manager::notes[i]->afficher(f);
    //}
for(Manager::IteratorNotes it=begin();it!=Manager::end();++it ){
    std::cout<<*it<<std::endl;
}
}




std::ostream& operator<<(std::ostream& f, const Note& n) {
        n.afficher(f);
        return f;}


 Manager& Manager::operator<<(Note& n){
    if (Manager::nbNotes==Manager::nbNotesMax){
        Note** newtab= new Note* [Manager::nbNotesMax+5];
        for(int i=0; i<Manager::nbNotes;i++){
            newtab[i]=Manager::notes[i];
        }
    nbNotesMax=nbNotesMax+5;
    Note** oldtab= Manager::notes;
    notes=newtab;
    delete [] oldtab;
    }
    Manager::notes[Manager::nbNotes]=n.clone();
    Manager::nbNotes=Manager::nbNotes+1;
    return *this;
    };


Article* Article::clone()const{
 Article* a=new Article(*this);
    return a;
}


Tache* Tache::clone()const{
    Tache* t=new Tache(*this);
    return t;}



/*
Multimedia* Multimedia::clone()const{
    return new Multimedia(*this);
}*/


Manager::~Manager(){

for(unsigned int i; i<nbNotes-1;i++){
    delete notes[i];
}
delete [] notes;
}

