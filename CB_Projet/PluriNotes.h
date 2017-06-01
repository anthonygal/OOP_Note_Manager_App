#ifndef PluriNotes_h
#define PluriNotes_h

#include "timing.h"
#include "Relations.h"
#include <string>
#include <typeinfo>



using namespace TIME;

enum NoteEtat{ active, archivee, corbeille };
enum TacheStatut{ attente, encours, terminee };
enum TypeMultimedia{ image, video, audio };

class Relation;
class Couple;
class Reference;
class Manager;

class Note{
private:
    unsigned long ID;
    std::string titre;
    TIME::Date dateCrea;
    TIME::Horaire horaireCrea;
    TIME::Date dateModif;
    TIME::Horaire horaireModif;
    NoteEtat etat;
    bool actuel;

public:
    Note(const unsigned long i, const std::string& s): ID(i),titre(s), dateCrea(dateNow()), horaireCrea(horaireNow()), dateModif(dateNow()), horaireModif(horaireNow()), etat(active), actuel(true){}//Pas besoin d'initialiser horaire et tout, sont initialiser à la construction
    Note(Note& n);

    unsigned long getID() const {return ID;}
    std::string getTitre() const { return titre; }
    const Date& getDateCrea() const { return dateCrea; } //Pourquoi Date et Horaire doivent passer un const contrairement a string ou autre type?
    const Date& getDateModif() const { return dateModif; } //Laisser ou enlever le const? La date de modif est ammenée à être modifié, mais on créera alors une nouvelle notes
    const Horaire& getHoraireCrea() const { return horaireCrea; }
    const Horaire& getHoraireModif() const { return horaireModif; }
    NoteEtat getEtat() const { return etat; } //0 pour active, 1 pour archivee et 2 pour corbeille
    bool getActuel() const { return actuel; }
    void setEtat(NoteEtat e){ etat=e; }
    void setActuel(){ actuel=true; }
    void setAncienne(){ actuel=false; }

    void afficher(std::ostream& f = std::cout) const;
    virtual void afficherSpecifique(std::ostream& f) const = 0;
    void AddRefs(Manager& m);
    virtual void AddRefsSpecifique(Manager& m)=0;
    virtual ~Note(){};
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
    Article(const unsigned long i, const std::string& ti, const std::string& te=""):Note(i,ti),texte(te){}
    Article(Article& a):Note(a),texte(a.texte){}

    std::string getTexte() const{ return texte; }
    void setTexte(const std::string& t){ texte=t; }

    void afficherSpecifique(std::ostream& f) const;
    void AddRefsSpecifique(Manager& m);
};

class Tache: public Note{
private:
    std::string action;
    TacheStatut statut;
    int priorite;
    TIME::Date echeance;

public:
    Tache(const unsigned long i, const std::string& ti, const std::string& act, int prio =0, Date d =Date(1,1,0)):Note(i,ti),action(act),statut(encours), priorite(prio), echeance(d){}
    Tache(Tache& t):Note(t),action(t.action),statut(t.statut),priorite(t.priorite),echeance(t.echeance){}

    std::string getAction() const { return action; }
    TacheStatut getStatut() const { return statut; }
    int getPriorite() const { return priorite; }
    TIME::Date getEcheance() const { return echeance; }
    void setAction(const std::string& act){ action = act; }
    void setStatut(const TacheStatut s){ statut = s; }
    void setPriorite(int p){ priorite = p; }
    void setEcheance(const TIME::Date& d){ echeance = d; }

    void afficherSpecifique(std::ostream& f) const;
    void AddRefsSpecifique(Manager& m);
};

class Multimedia: public Note{
private:
    std::string adresseFichier;
    TypeMultimedia type;
    std::string description;

public:
    Multimedia(const unsigned long i, const std::string& ti, const std::string& adr, TypeMultimedia ty=image, const std::string& desc=""):Note(i,ti),adresseFichier(adr),type(ty),description(desc){}
    Multimedia(Multimedia& m):Note(m),adresseFichier(m.adresseFichier),description(m.description),type(m.type){}

    std::string getAdresseFichier() const { return adresseFichier; }
    std::string getDescription() const { return description; }
    TypeMultimedia getType() const { return type; }
    void setAdresseFichier(const std::string& adr){ adresseFichier = adr; }
    void setDescription(const std::string& desc){ description = desc; }
    void setType(const TypeMultimedia ty){ type = ty; }

    void afficherSpecifique(std::ostream& f) const;
    void AddRefsSpecifique(Manager& m);
};

//Manager gere tout !

class Manager{
private:
    static Manager* InstanceUnique;

    unsigned int nbNotes;
    unsigned int nbNotesMax;
    Note** notes;

    unsigned int nbRelations;
    unsigned int nbRelationsMax;
    Relation** relations;

    Manager(): nbNotes(0), nbNotesMax (5), notes(new Note*[nbNotesMax]), nbRelations(0), nbRelationsMax(5), relations(new Relation*[100]){};
    Manager(const Manager&);
    void operator=(const Manager&);
    ~Manager();

public:
    static Manager& donneInstance();
    static void libereInstance();

   class IteratorNotes{
   private:
        friend class Manager;
        Note** currentN;
        int remain;
        IteratorNotes(Note** t, int n): currentN(t), remain(n){}
   public:
       bool isDone() const { return !remain; }
       void next();
       Note& current() const;
    };

    class ConstIteratorNotes{
    private:
        friend class Manager;
        Note** currentN;
        int remain;
        ConstIteratorNotes(Note** t, int n): currentN(t), remain(n){}
    public:
       bool isDone() const { return !remain; }
       void next();
       const Note& current() const;
    };

    IteratorNotes begin() const {return IteratorNotes(notes, nbNotes);}
    IteratorNotes end()const{return IteratorNotes(notes+nbNotes,0);}
    IteratorNotes begin1()const{return IteratorNotes(notes-1,nbNotes);}
    IteratorNotes end1() const{return IteratorNotes(notes+nbNotes-1,0);}
    int getnbNotes()const {return nbNotes;}
    int getnbRelations() const {return nbRelations;}
    Reference& getReference();
    Note* SearchID(unsigned long id);

    void Affichertout() const;

    Article& NewArticle(const unsigned long i, const std::string& ti, const std::string& te="");
    Tache& NewTache(const unsigned long i, const std::string& ti, const std::string& act, int prio =0, Date d =Date (1,1,0));
    Multimedia& NewMultimedia(const unsigned long i, const std::string& ti, const std::string& adr, const std::string& desc="", TypeMultimedia ty=image);

    Article& editTexteArticle(Article& A, const std::string& s);
    Tache& editActionTache(Tache& T, const std::string& s);
    Tache& editStatutTache(Tache& T, TacheStatut s);
    Tache& editPrioriteTache(Tache& T, int p);
    Tache& editEcheanceTache(Tache& T, TIME::Date d);
    Multimedia& editFichierMultimedia(Multimedia& M, const std::string s);

    Manager& operator<<(Note& n);

    void addRelation(Relation& r);
    void addCoupleRelation(Relation& r, Couple& c);
    void addCoupleReference(Couple& c);
    void AddRefsFromNote(Note& N);
};


std::ostream& operator<<(std::ostream& f , const Note& n);



//Classe d'Exception

class NoteException{
private:
    std::string info;
public:
    NoteException(const std::string& s): info(s){}
    std::string getInfo() const {return info;}
};

#endif /* PluriNotes_h */
