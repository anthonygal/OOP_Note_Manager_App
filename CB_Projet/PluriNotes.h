#ifndef PluriNotes_h
#define PluriNotes_h

#include "timing.h"
#include <string>
#include <typeinfo>


using namespace TIME;

enum NoteEtat{ active, archivee, corbeille };
enum TacheStatut{ attente, encours, terminee };
enum TypeMultimedia{ image, video, audio };

class Relation;
class Couple;
class Reference;

class Note{
private:
    int ID;
    std::string titre;
    TIME::Date dateCrea;
    TIME::Horaire horaireCrea;
    TIME::Date dateModif;
    TIME::Horaire horaireModif;
    NoteEtat etat;
    bool actuel;

public:
    Note(const unsigned int i, const std::string& s): ID(i),titre(s), dateCrea(dateNow()), horaireCrea(horaireNow()), dateModif(dateNow()), horaireModif(horaireNow()), etat(active), actuel(true){}//Pas besoin d'initialiser horaire et tout, sont initialiser à la construction
    Note(Note& n);
    Note (const Note& n);
    virtual Note* clone()const=0; //Comprend pas ca + BUG ^^
    
    int getID() const {return ID;}
    std::string getTitre() const { return titre; }
    const Date& getDateCrea() const { return dateCrea; } //Pourquoi Date et Horaire doivent passer un const contrairement a string ou autre type?
    const Date& getDateModif() const { return dateModif; } //Laisser ou enlever le const? La date de modif est ammenée à être modifié, mais on créera alors une nouvelle notes
    const Horaire& getHoraireCrea() const { return horaireCrea; }
    const Horaire& getHoraireModif() const { return horaireModif; }
    NoteEtat getEtat() const { return etat; } //0 pour active, 1 pour archivee et 2 pour corbeille
    bool getActuel() const { return actuel; }
    void setEtat(NoteEtat e){ etat=e; }
    void setActuel(bool b){actuel=b;}
    void setModif(){dateModif=dateNow(); horaireModif=horaireNow();};

    void afficher(std::ostream& f = std::cout) const;
    virtual void affichageSpecifique(std::ostream& f) const = 0;
    //virtual ~Note();
};

/*
 COMMENTAIRES A PRENDRE EN COMPTE:
    -Pour la gestion des type dates horaire etc... on reprendra les fichiers timing.h et timing.cpp donnés en ressources lors du TD7
    -Les accesseurs en edition créeent la nouvelle version de la note prenant les modifications souhaitées en compte et renvoyeent l'addresse de la nouvelle version de la note créer
    -La seule utilité de la methode virtuelle pure estAbstraite() est de rendre la classe Note abstraite. Son comportement (ne fait rien du tout) est défini dans les sous classe afin de rendre ces sous classes concrètes. Cette fonction pourra ne sera plus necessaire si une methode virtuelle pure utile vient à etre implementée plus tard
    - Une classe: Ordre des méthodes: 1/ Constructeur 2/ get  3/ set (Pas sûr qu'on en utilise)=> sera gérer par le manager  4/ Autres fonctions
 */

class Article: public Note{
private:
    std::string texte;

public:
    Article(const unsigned int i, const std::string& ti, const std::string& te=""):Note(i,ti),texte(te){}
    Article(const Article& a):Note(a.getID(),a.getTitre()),texte(a.texte){};
    Article* clone()const; // Je vois pas a quoi ca sert Antoine?

    std::string getTexte() const{ return texte; }
    void setTexte(const std::string& t){ texte=t; }

    void affichageSpecifique(std::ostream& f) const;

};


class Tache: public Note{
private:
    std::string action;
    TacheStatut statut;
    int priorite;
    TIME::Date echeance;
    //virtual void estAbstraite(){};

public:
    Tache(const unsigned int i, const std::string& ti, const std::string& act, int prio =0, Date d =Date (1,1,0)):Note(i,ti),action(act),statut(encours), priorite(prio), echeance(d){}
    Tache* clone() const;

    std::string getAction() const { return action; }
    TacheStatut getStatut() const { return statut; }
    int getPriorite() const { return priorite; }
    TIME::Date getEcheance() const { return echeance; }
    void setAction(const std::string& act){ action = act; }
    void setStatut(const TacheStatut s){ statut = s; }
    void setPriorite(int p){ priorite = p; }
    void setEcheance(const TIME::Date& d){ echeance = d; }

    void affichageSpecifique(std::ostream& f) const;
};


class Multimedia: public Note{
private:
    std::string adresseFichier;
    std::string description;
    TypeMultimedia type;

public:
    Multimedia(const unsigned int i, const std::string& ti, const std::string& adr, const std::string& desc="", TypeMultimedia ty=image):Note(i,ti),adresseFichier(adr),description(desc),type(ty){}
    Multimedia* clone() const; // Je vois pas a quoi ca sert Antoine?

    std::string getAdresseFichier() const { return adresseFichier; }
    std::string getDescription() const { return description; }
    TypeMultimedia getType() const { return type; }
    void setAdresseFichier(const std::string& adr){ adresseFichier = adr; }
    void setDescription(const std::string& desc){ description = desc; }
    void setType(const TypeMultimedia ty){ type = ty; }

    void affichageSpecifique(std::ostream& f) const;
};



class Manager{
private:
    unsigned int nbNotes;
    unsigned int nbNotesMax;
    Note** notes;
    
    unsigned int nbRelations;
    unsigned int nbRelationsMax;
    Relation** relations;
    
public:
    Manager(): nbNotes(0), nbNotesMax (5), notes (new Note*[nbNotesMax]){};
   class IteratorNotes {
   private:
        friend class Manager;
        int nb;
        Note** courant;
        IteratorNotes (Note** t, int n): courant(t), nb(n){}
   public:
       bool operator!=(const IteratorNotes& it) {return courant!=it.courant;}
       const Note& operator*() {return **courant;}
       IteratorNotes& operator++() {courant++; return *this;}
       IteratorNotes& operator--() {courant--; return *this;}
   } ;
    IteratorNotes begin()const{return IteratorNotes(notes, nbNotes);}
    IteratorNotes end()const{return IteratorNotes(notes+nbNotes,0);}
    IteratorNotes begin1()const{return IteratorNotes(notes-1,nbNotes);}
    IteratorNotes end1() const{return IteratorNotes(notes+nbNotes-1,0);}
    int getnbNotes()const {return nbNotes;}

    void Affichertout() const;
    
    
    Article& editTexteArticle(Article& A, const std::string& s);
    Tache& editActionTache(Tache& T, const std::string& s);
    Tache& editStatutTache(Tache& T, TacheStatut s);
    Tache& editPrioriteTache(Tache& T, int p);
    Tache& editEcheanceTache(Tache& T, TIME::Date d);
    Multimedia& editFichierMultimedia(Multimedia& M, const std::string s);
    
    Manager& operator<<(Note& n);
    
    void addRelation(Relation& r);
    void addCoupleRelation(Relation& r, Couple& c);
    
    
    
    ~Manager();


};

std::ostream& operator<<(std::ostream& f , const Note& n);




#endif /* PluriNotes_h */
