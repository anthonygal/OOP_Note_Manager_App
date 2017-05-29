#include "PluriNotes.h"
#include "Relations.h"

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
    n.setActuel(true);
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
    f<<"\n ID : "<<ID;
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
        case 2: f<<"Terminee"; break;}
    if (priorite!=0){
    f<<"\nPriorite : "<<priorite;
    }
    if (echeance.getAnnee()!=0 || echeance.getMois()!=1 ||echeance.getJour()!=1  ){
    f<<"\nEcheance : "<<echeance;
    }

}


void Multimedia::affichageSpecifique(std::ostream& f) const {}


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


Multimedia* Multimedia::clone() const {
    Multimedia* m=new Multimedia(*this);
    return m;
};

void Manager::addRelation(Relation& r){
    if (nbRelations==nbRelationsMax){
        Relation** newtab= new Relation* [nbRelationsMax+100];
        for(int i=0; i<nbRelations;i++){
            newtab[i]=relations[i];
        }
        nbRelationsMax=nbRelationsMax+100;
        Relation** oldtab= relations;
        relations=newtab;
        delete [] oldtab;
    }
    relations[nbRelations]=&r;
    nbRelations++;
}

void addCoupleRelation(Relation& r, Couple& c) {
    r.addCouple(c);
}

Manager::~Manager(){
    
    for(unsigned int i = 0; i<nbNotes;i++){
        delete notes[i]; //un destructeur virtuel pour Note à definir à 'mment donné il me semble
    }
    delete [] notes;
    
    for(unsigned int i = 0; i<nbRelations;i++){
        delete relations[i];
    }
    delete [] relations;
}


//Recherche de notes à partir d'un ID
Note* Manager::SearchID(unsigned long id){
    IteratorNotes it=begin();
    Note& n=*it;
    int i=0;
    while (n.getID()!=id && i<nbNotes) {
        ++it;
        n=*it;
        if (n.getActuel()) return &n;
        }
    return nullptr;
}


//EDITEURS DE NOTES DE LA CLASSE MANAGER CREANT UNE NOUVELLE VERSION DE LA NOTES ET L AJOUTANT AU TABLEAU notes DU MANAGER (PARTIE 1.2 DU SUJET DE PROJET):


Article& Manager::editTexteArticle(Article& A, const std::string& s) {
    Article* a= new Article(A);
    a->setTexte(s);
    a->setModif();
    a->setActuel(true);
    A.setActuel(false);
    *this<<*a;
    return *a;
}

Tache& Manager::editActionTache(Tache& T, const std::string& s){
    Tache* t= new Tache(T);
    t->setAction(s);
    t->setModif();
    t->setActuel(true);
    T.setActuel(false);
    *this<<*t;
    return *t;
};

Tache& Manager::editStatutTache(Tache& T, TacheStatut s){
    Tache* t= new Tache(T);
    t->setStatut(s);
    t->setModif();
    t->setActuel(true);
    T.setActuel(false);
    *this<<*t;
    return *t;
};

Tache& Manager::editPrioriteTache(Tache& T, int p){
    Tache* t= new Tache(T);
    t->setPriorite(p);
    t->setModif();
    t->setActuel(true);
    T.setActuel(false);
    *this<<*t;
    return *t;};

Tache& Manager::editEcheanceTache(Tache& T, TIME::Date d){
    Tache* t= new Tache(T);
    t->setEcheance(d);
    t->setModif();
    t->setActuel(true);
    T.setActuel(false);
    *this<<*t;
    return *t;
};

Multimedia& Manager::editFichierMultimedia(Multimedia& M, const std::string s){
    Multimedia* m= new Multimedia(M);
    m->setAdresseFichier(s);
    m->setModif();
    m->setActuel(true);
    M.setActuel(false);
    *this<<*m;
    return *m;
};





//Singleton pour classe Manager

Manager* Manager::InstanceUnique=nullptr;

Manager& Manager::donneInstance(){
    if (InstanceUnique==nullptr) InstanceUnique= new Manager;
    return *InstanceUnique;
}

void Manager::libereInstance(){
    if (InstanceUnique!=nullptr)
        delete InstanceUnique;
    InstanceUnique=nullptr;
}

//Ajouter un couple à la relation reference

void addCoupleReference(Couple& c){
    Reference& R=Reference::donneInstance();
    R.addCouple(c);
}

// Ajout de toutes les references contenues dans les champs de texte d'une notes avec Template Method

void Note::AddRefs(Manager& m){
    unsigned long ID=findRefID(this->getTitre(), 0);
    int pos=0;
    while (ID!=0){
        Note* N=m.SearchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getTitre(), pos);
    }
    AddRefsSpecifique(m);
}

//AddrefsSpeacifique(Manager& m) Specifique a chaque sous class de Note

void Tache::AddRefsSpecifique(Manager& m){
    unsigned long ID=findRefID(this->getAction(), 0);
    int pos=0;
    while (ID!=0){
        Note* N=m.SearchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getAction(), pos);
    }
}

void Article::AddRefsSpecifique(Manager& m){
    unsigned long ID=findRefID(this->getTexte(), 0);
    int pos=0;
    while (ID!=0){
        Note* N=m.SearchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getTexte(), pos);
    }
}

void Multimedia::AddRefsSpecifique(Manager& m){
    unsigned long ID=findRefID(this->getDescription(), 0);
    int pos=0;
    while (ID!=0){
        Note* N=m.SearchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getDescription(), pos);
    }
}

//AddRefsFromNote du Manager qui permet d'ajouter toute les references contenues dans tous les champs de texte d'une Note

void Manager::AddRefsFromNote(Note& N){
    N.AddRefs(*this);
}
