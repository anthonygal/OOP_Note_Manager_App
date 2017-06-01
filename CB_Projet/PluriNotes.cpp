#include "PluriNotes.h"

using namespace TIME;

/**< CONSTRUCTEUR DE RECOPIE DE LA CLASS NOTE */

Note::Note(Note& n){
    ID = n.ID;
    titre = n.titre;
    dateCrea = n.dateCrea;
    horaireCrea = n.horaireCrea;
    dateModif = dateNow();
    horaireModif = horaireNow();
    etat = n.etat;
    actuel = true;
    n.setAncienne();
}

/**< METHODES D'AFFICHAGE DES DIFFERENTES NOTES */

void Note::afficher(std::ostream& f) const {
    f<<"\n------ "<<typeid(*this).name()<<" "<<ID<<(actuel?" (Version Actuelle)":" (Ancienne Version)")<<" ------\n";
    f<<"\nID : "<<ID;
    f<<"\nTitre : "<<titre;
    f<<"\nCree le : "<<dateCrea<<" a "<<horaireCrea;
    f<<"\nModifie le "<<dateModif<<" a "<<horaireModif;
    f<<"\nEtat : ";
    switch(etat){
        case 0: f<<"Active"; break;
        case 1: f<<"Archivee"; break;
        case 2: f<<"Dans la corbeille"; break;
    }
    afficherSpecifique(f);
    f<<"\n\n-------\n";
}

void Article::afficherSpecifique(std::ostream& f) const {
    f<<"\nTexte : "<<texte;
}

void Tache::afficherSpecifique(std::ostream& f) const {
    f<<"\nAction : "<<action;
    f<<"\nStatut : ";
    switch(statut){
        case 0: f<<"Attente"; break;
        case 1: f<<"En cours"; break;
        case 2: f<<"Terminee"; break;}
    if (priorite!=0){
    f<<"\nPriorite : "<<priorite;
    }
    if (echeance.getAnnee()!=0 || echeance.getMois()!=1 || echeance.getJour()!=1  ){
    f<<"\nEcheance : "<<echeance;
    }
}

void Multimedia::afficherSpecifique(std::ostream& f) const {
    f<<"\nAdresseFichier : "<<adresseFichier;
    f<<"\nDescription : "<<description;
    f<<"\nType : ";
    switch(type){
        case 0: f<<"image"; break;
        case 1: f<<"video"; break;
        case 2: f<<"audio"; break;}
}

std::ostream& operator<<(std::ostream& f, const Note& n) {
        n.afficher(f);
        return f;
}

void Manager::afficherTout()const{
    for(ConstIteratorNotes it=getConstIteratorNotes();!it.isDone();it.next()) std::cout<<it.current()<<std::endl;
}

/**< TEMPLATE METHOD SINGLETON POUR LA CLASS MANAGER */

Manager* Manager::InstanceUnique=nullptr;

Manager& Manager::donneInstance(){
    if (InstanceUnique==nullptr) InstanceUnique = new Manager;
    return *InstanceUnique;
}

void Manager::libereInstance(){
    if (InstanceUnique!=nullptr)
        delete InstanceUnique;
    InstanceUnique=nullptr;
}

Manager::~Manager(){

    for(unsigned int i = 0; i<nbNotes;i++){
        delete notes[i]; //un destructeur virtuel pour Note à definir à 'mment donné il me semble
    }
    delete[] notes;

    for(unsigned int i = 0; i<nbRelations;i++){
        delete relations[i];
    }
    delete[] relations;
}

/**< TEMPLATE METHOD ITERATOR DANS LA CLASSE MANAGER POUR LES NOTES */

void Manager::IteratorNotes::next(){
    if(isDone()) throw NoteException("\nnext() sur un IteratorNotes fini !\n");
    remain--;
    currentN++;
}

Note& Manager::IteratorNotes::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un IteratorNotes fini !\n");
    return **currentN;
}

void Manager::ConstIteratorNotes::next(){
    if(isDone()) throw NoteException("\nnext() sur un ConstIteratorNotes fini !\n");
    remain--;
    currentN++;
}

const Note& Manager::ConstIteratorNotes::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un ConstIteratorNotes fini !\n");
    return **currentN;
}

/**< TEMPLATE METHOD ITERATOR DANS LA CLASSE MANAGER POUR LES RELATIONS */

void Manager::IteratorRelations::next(){
    if(isDone()) throw NoteException("\nnext() sur un IteratorRelation fini !\n");
    remain--;
    currentR++;
}

Relation& Manager::IteratorRelations::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un IteratorRelation fini !\n");
    return **currentR;
}

void Manager::ConstIteratorRelations::next(){
    if(isDone()) throw NoteException("\nnext() sur un ConstIteratorRelation fini !\n");
    remain--;
    currentR++;
}

const Relation& Manager::ConstIteratorRelations::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un ConstIteratorRelation fini !\n");
    return **currentR;
}

/**< METHODES DE CREATION DES DIFFERENTS NOTES */

unsigned long Manager::nextNoteID = 0;

void Manager::newArticle(const std::string& ti, const std::string& te){
    Article* a=new Article(nextNoteID++,ti,te);
    ajouterNote(*a);
}

void Manager::newTache(const std::string& ti, const std::string& act, int prio, Date d){
    Tache* a=new Tache(nextNoteID++,ti,act,prio,d);
    ajouterNote(*a);
}

void Manager::newMultimedia(const std::string& ti, const std::string& adr, const std::string& desc, TypeMultimedia ty){
    Multimedia* a=new Multimedia(nextNoteID++,ti,adr,ty,desc);
    ajouterNote(*a);
}

void Manager::ajouterNote(Note& n){
    if(nbNotes == nbNotesMax){
        Note** newtab = new Note* [Manager::nbNotesMax+5];
        for(unsigned int i=0;i<nbNotes;i++) newtab[i] = notes[i];
        Note** oldtab = notes;
        notes = newtab;
        nbNotesMax += 5;
        delete[] oldtab;
    }
    notes[nbNotes++] = &n;
};

/**< DEMANDES D'EDITION DES DIFFERENTS NOTES */
/**< MODIFIER LES CIN/COUT LORS DE LA MISE EN PLACE DE QT */

void Manager::editNote(Note& n){
    Note& n2=n.edit();
    ajouterNote(n2);
}

Article& Article::edit(){
    std::string newTitle;
    std::string newText;
    std::cout<<"\nAncien titre : "<<this->getTitre()<<"\tNouveau titre : ";
    std::cin>>newTitle;
    std::cout<<"\nAncien texte : "<<this->getTexte()<<"\tNouveau texte : ";
    std::cin>>newText;
    Article* a=new Article(*this);
    a->setTitre(newTitle);
    a->setTexte(newText);
    return *a;
}

Tache& Tache::edit(){
    std::string newTitle;
    std::string newAction;
    int newPriorite;
    TIME::Date newEcheance;
    std::cout<<"\nAncien titre : "<<this->getTitre()<<"\tNouveau titre : ";
    std::cin>>newTitle;
    std::cout<<"\nAncienne action : "<<this->getAction()<<"\tNouvelle action : ";
    std::cin>>newAction;
    std::cout<<"\nAncienne priorite : "<<this->getPriorite()<<"\tNouvelle priorite : ";
    std::cin>>newPriorite;
    std::cout<<"\nAncienne date d'echeance : "<<this->getEcheance()<<"\tNouvelle date d'echeance : ";
    std::cin>>newEcheance;
    Tache* t=new Tache(*this);
    t->setTitre(newTitle);
    t->setAction(newAction);
    t->setPriorite(newPriorite);
    t->setEcheance(newEcheance);
    return *t;
}

Multimedia& Multimedia::edit(){
    std::string newTitle;
    std::string newAdresseFichier;
    std::string newTypeString;
    TypeMultimedia newType;
    std::string newDescription;
    std::cout<<"\nAncien titre : "<<this->getTitre()<<"\tNouveau titre : ";
    std::cin>>newTitle;
    std::cout<<"\nAncienne adresse fichier : "<<this->getAdresseFichier()<<"\tNouvelle adresse fichier : ";
    std::cin>>newAdresseFichier;
    do{
        std::cout<<"\nAncienne type : "<<this->getType()<<"\tNouveau type (choisir entre image/video/audio) : ";
        std::cin>>newTypeString;
    }while(newTypeString!="image" && newTypeString!="video" && newTypeString!="audio");
    if(newTypeString=="image") newType=image;
    if(newTypeString=="video") newType=video;
    if(newTypeString=="audio") newType=audio;
    std::cout<<"\nAncienne description : "<<this->getDescription()<<"\tNouvelle description : ";
    std::cin>>newDescription;
    Multimedia* m=new Multimedia(*this);
    m->setTitre(newTitle);
    m->setAdresseFichier(newAdresseFichier);
    m->setType(newType);
    m->setDescription(newDescription);
    return *m;
}

/**< METHODES D'AJOUT DE RELATIONS */

void Manager::addRelation(Relation& r){
    if (nbRelations==nbRelationsMax){
        Relation** newtab= new Relation* [nbRelationsMax+5];
        for(unsigned int i=0; i<nbRelations;i++){
            newtab[i]=relations[i];
        }
        nbRelationsMax=nbRelationsMax+5;
        Relation** oldtab= relations;
        relations=newtab;
        delete [] oldtab;
    }
    relations[nbRelations]=&r;
    nbRelations++;
}

void Manager::addCoupleRelation(Relation& r, Couple& c) {
    r.addCouple(c);
}

/**< TEMPLATE METHOD SINGLETON POUR LA CLASS REFERENCE */

Reference& Manager::getReference() {
    Reference& R=Reference::donneInstance();
    return R;
}

/**< Methode permettant de rechercher une note à partir d'un ID */
Note* Manager::searchID(unsigned long id){
    for (unsigned int i=0; i<nbNotes;i++){
        if (notes[i]->getID()==id){
            if (notes[i]->getActuel()) {
                return notes[i];
            }
        }
    }
    return nullptr;
}

/**< Methodes d'edition inutiles pour l'instant mais je prefere garder au cas ou */

Article& Manager::editTexteArticle(Article& A, const std::string& s) {
    Article* a= new Article(A);
    a->setTexte(s);
    a->setActuel();
    A.setAncienne();
    ajouterNote(*a);
    return *a;
}

Tache& Manager::editActionTache(Tache& T, const std::string& s){
    Tache* t= new Tache(T);
    t->setAction(s);
    t->setActuel();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
};

Tache& Manager::editStatutTache(Tache& T, TacheStatut s){
    Tache* t= new Tache(T);
    t->setStatut(s);
    t->setActuel();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
};

Tache& Manager::editPrioriteTache(Tache& T, int p){
    Tache* t= new Tache(T);
    t->setPriorite(p);
    t->setActuel();
    T.setAncienne();
    ajouterNote(*t);
    return *t;};

Tache& Manager::editEcheanceTache(Tache& T, TIME::Date d){
    Tache* t= new Tache(T);
    t->setEcheance(d);
    t->setActuel();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
};

Multimedia& Manager::editFichierMultimedia(Multimedia& M, const std::string s){
    Multimedia* m= new Multimedia(M);
    m->setAdresseFichier(s);
    m->setActuel();
    M.setAncienne();
    ajouterNote(*m);
    return *m;
};

//Ajouter un couple à la relation reference

void Manager::addCoupleReference(Couple& c){
    Reference& R=this->getReference();
    R.addCouple(c);
}

// Ajout de toutes les references contenues dans les champs de texte d'une notes avec Template Method

void Note::AddRefs(Manager& m){
    unsigned long ID=findRefID(this->getTitre(), 0);
    int pos=0;
    while (ID!=0){
        Note* N=m.searchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            m.addCoupleReference(*C);
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
        Note* N=m.searchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            m.addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getAction(), pos);
        ID=findRefID(this->getAction(), pos);
    }
}

void Article::AddRefsSpecifique(Manager& m){
    unsigned long ID=findRefID(this->getTexte(), 0);
    int pos=0;
    while (ID!=0){
        Note* N=m.searchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            m.addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getTexte(), pos);
        ID=findRefID(this->getTexte(), pos);
    }
}

void Multimedia::AddRefsSpecifique(Manager& m){
    unsigned long ID=findRefID(this->getDescription(), 0);
    int pos=0;
    while (ID!=0){
        Note* N=m.searchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            m.addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getDescription(), pos);
        ID=findRefID(this->getDescription(), pos);
    }
}

//AddRefsFromNote du Manager qui permet d'ajouter toute les references contenues dans tous les champs de texte d'une Note

void Manager::AddRefsFromNote(Note& N){
    N.AddRefs(*this);
}
