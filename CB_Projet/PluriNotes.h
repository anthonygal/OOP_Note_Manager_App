#ifndef PluriNotes_h
#define PluriNotes_h

#include "timing.h"
#include "Relations.h"
#include <string>
#include <typeinfo>
#include <sstream>

using namespace TIME;

enum NoteEtat{ active, archivee, corbeille }; /**< Les differents etats d'une Note */
enum TacheStatut{ attente, encours, terminee }; /**< Les differents statuts d'une Tache */
enum TypeMultimedia{ image, video, audio }; /**< Les differents types de fichier Multimedia */

class Relation;
class Couple;
class Reference;
class Manager;

/**< CLASSE EXCEPTION */
class NoteException{
private:
    std::string info;
public:
    NoteException(const std::string& s): info(s){}
    std::string getInfo() const {return info;}
};

/**< CLASSE ABSTRAITE NOTE */
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
    /**< Constructeurs */
    Note(const unsigned long i, const std::string& s): ID(i),titre(s), dateCrea(dateNow()), horaireCrea(horaireNow()), dateModif(dateNow()), horaireModif(horaireNow()), etat(active), actuel(true){}
    Note(Note& n);
    /**< Destructeur */
    virtual ~Note(){};
    /**< Requetes getAttributs */
    unsigned long getID() const {return ID;}
    std::string getTitre() const {return titre;}
    const Date& getDateCrea() const {return dateCrea;} //Pourquoi Date et Horaire doivent passer un const contrairement a string ou autre type?
    const Date& getDateModif() const {return dateModif;}
    const Horaire& getHoraireCrea() const {return horaireCrea;}
    const Horaire& getHoraireModif() const {return horaireModif;}
    NoteEtat getEtat() const {return etat;} /**< etat vaut 0 pour active, 1 pour archivee et 2 pour corbeille */
    bool getActuel() const {return actuel;}
    /**< Commandes setAttributs */
    void setTitre(const std::string ti){titre=ti;}
    void setEtat(NoteEtat e){etat=e;}
    void setActuel(){actuel=true;}
    void setAncienne(){actuel=false;}
    /**< Methode d'edition */
    virtual Note& edit()=0;
    /**< Methodes d'affichage */
    void afficher(std::ostream& f = std::cout) const;
    virtual void afficherSpecifique(std::ostream& f) const = 0;
    /**< Methodes pour ajouter des references */
    void AddRefs(Manager& m);
    virtual void AddRefsSpecifique(Manager& m)=0;
};

/**< Surcharge de l'operateur << pour afficher une note avec ce dernier */
std::ostream& operator<<(std::ostream& f , const Note& n);

/**< CLASSE ARTICLE FILLE DE NOTE */
class Article: public Note{
private:
    std::string texte;
public:
    /**< Constructeurs d'Article */
    Article(const unsigned long i, const std::string& ti, const std::string& te=""):Note(i,ti),texte(te){}
    Article(Article& a):Note(a),texte(a.texte){}
    /**< Destructeur d'Article */
    ~Article(){}
    /**< Requetes getAttributs */
    std::string getTexte() const{return texte;}
    /**< Commandes setAttributs */
    void setTexte(const std::string& t){texte=t;}
    /**< Methode d'edition */
    Article& edit();
    /**< Methode d'affichage specifique */
    void afficherSpecifique(std::ostream& f) const;
    /**< Methode pour ajouter des references specifique */
    void AddRefsSpecifique(Manager& m);
};

/**< CLASSE TACHE FILLE DE NOTE */
class Tache: public Note{
private:
    std::string action;
    int priorite;
    TIME::Date echeance;
    TacheStatut statut;
public:
    /**< Constructeurs de Tache */
    Tache(const unsigned long i, const std::string& ti, const std::string& act, int prio=0, Date d=Date(1,1,0)):Note(i,ti),action(act),priorite(prio),echeance(d),statut(encours){}
    Tache(Tache& t):Note(t),action(t.action),priorite(t.priorite),echeance(t.echeance),statut(t.statut){}
    /**< Destructeur de Tache */
    ~Tache(){}
    /**< Requetes getAttributs */
    std::string getAction() const {return action;}
    TacheStatut getStatut() const {return statut;}
    int getPriorite() const {return priorite;}
    TIME::Date getEcheance() const {return echeance;}
    /**< Commandes setAttributs */
    void setAction(const std::string& act){action=act;}
    void setStatut(const TacheStatut s){statut=s;}
    void setPriorite(int p){priorite=p;}
    void setEcheance(const TIME::Date& d){echeance=d;}
    /**< Methode d'edition */
    Tache& edit();
    /**< Methode d'affichage specifique */
    void afficherSpecifique(std::ostream& f) const;
    /**< Methode pour ajouter des references specifique */
    void AddRefsSpecifique(Manager& m);
};

/**< CLASSE MULTIMEDIA FILLE DE NOTE */
class Multimedia: public Note{
private:
    std::string adresseFichier;
    TypeMultimedia type;
    std::string description;
public:
    /**< Constructeurs de Multimedia */
    Multimedia(const unsigned long i, const std::string& ti, const std::string& adr, TypeMultimedia ty=image, const std::string& desc=""):Note(i,ti),adresseFichier(adr),type(ty),description(desc){}
    Multimedia(Multimedia& m):Note(m),adresseFichier(m.adresseFichier),type(m.type),description(m.description){}
    /**< Destructeur de Multimedia */
    ~Multimedia(){}
    /**< Requetes getAttributs */
    std::string getAdresseFichier() const {return adresseFichier;}
    std::string getDescription() const {return description;}
    TypeMultimedia getType() const {return type;}
    /**< Commandes setAttributs */
    void setAdresseFichier(const std::string& adr){adresseFichier=adr;}
    void setDescription(const std::string& desc){description=desc;}
    void setType(const TypeMultimedia ty){type=ty;}
    /**< Methode d'edition */
    Multimedia& edit();
    /**< Methode d'affichage specifique */
    void afficherSpecifique(std::ostream& f) const;
    /**< Methode pour ajouter des references specifique */
    void AddRefsSpecifique(Manager& m);
};

/**< CLASS MANAGER QUI GERE TOUT */
class Manager{
private:
    static Manager* InstanceUnique; /**< L'unique Manager : Singleton */
    static unsigned long nextNoteID; /**< La prochaine note qui sera crée se verra attribuer cet ID */
    unsigned int nbNotes; /**< Tableau de Notes */
    unsigned int nbNotesMax;
    Note** notes;
    unsigned int nbRelations; /**< Tableau de Relations */
    unsigned int nbRelationsMax;
    Relation** relations;
    Manager(): nbNotes(0), nbNotesMax(5), notes(new Note*[nbNotesMax]), nbRelations(0), nbRelationsMax(5), relations(new Relation*[100]){} /**< Constructeur de Manager */
    Manager(const Manager&); /**< Constructeur de recopie de Manager */
    void operator=(const Manager&); /**< Surcharge de l'operateur = pour affecter un Manager */
    ~Manager(); /**< Destructeur Manager */
    void ajouterNote(Note& n); /**< Methode pour ajouter une Note, utilisee dans les methodes de creation et d'edition d'article/tache/multimedia */
public:
    /**< Template Method Singleton */
    static Manager& donneInstance();
    static void libereInstance();
    /**< Iterateur pour notes */
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
    IteratorNotes getIteratorNotes() const {return IteratorNotes(notes, nbNotes);}
    /**< Iterateur constant pour notes  */
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
    ConstIteratorNotes getConstIteratorNotes() const {return ConstIteratorNotes(notes, nbNotes);}
    /**< Iterateur pour relations */
    class IteratorRelations{
    private:
        friend class Manager;
        Relation** currentR;
        int remain;
        IteratorRelations(Relation** t, int n): currentR(t), remain(n){}
    public:
        bool isDone() const { return !remain; }
        void next();
        Relation& current() const;
    };
    IteratorRelations getIteratorRelations() const {return IteratorRelations(relations, nbRelations);}
    /**< Iterateur constant pour relations  */
    class ConstIteratorRelations{
    private:
        friend class Manager;
        Relation** currentR;
        int remain;
        ConstIteratorRelations(Relation** t, int n): currentR(t), remain(n){}
    public:
        bool isDone() const { return !remain; }
        void next();
        const Relation& current() const;
    };
    ConstIteratorRelations getConstIteratorRelations() const {return ConstIteratorRelations(relations, nbRelations);}
    /**< Je sais pas quoi ecrire */
    int getNbNotes()const {return nbNotes;}
    int getNbRelations() const {return nbRelations;}
    Note** getNotes() const {return notes;}
    Reference& getReference();
    Note* searchID(unsigned long id);
    /**< Methode pour afficher toutes les notes */
    void afficherTout() const;
    /**< Methodes pour ajouter un Article/Tache/Multimedia au tableau de notes*/
    void newArticle(const std::string& ti, const std::string& te=""); /**< creation d'un article */
    void newTache(const std::string& ti, const std::string& act, int prio=0, Date d=Date(1,1,0)); /**< creation d'une tache */
    void newMultimedia(const std::string& ti, const std::string& adr, const std::string& desc="", TypeMultimedia ty=image); /**< creation d'un multimedia */
    /**< Methode pour editer une note */
    void editNote(Note& n);
    /**< Methodes d'edition inutiles pour l'instant mais je prefere garder au cas ou */
    Article& editTexteArticle(Article& A, const std::string& s);
    Tache& editActionTache(Tache& T, const std::string& s);
    Tache& editStatutTache(Tache& T, TacheStatut s);
    Tache& editPrioriteTache(Tache& T, int p);
    Tache& editEcheanceTache(Tache& T, TIME::Date d);
    Multimedia& editFichierMultimedia(Multimedia& M, const std::string s);
    /**< Methodes d'ajout de Relation/Reference */
    void addRelation(Relation& r);
    void addCoupleRelation(Relation& r, Couple& c);
    void addCoupleReference(Couple& c);
    void AddRefsFromNote(Note& N);
    //Methode permettant de savoir si une note est referencee
    bool isReferenced(const Note& N) const;
    //Supression ou Archivage de Note
    void supprimer(Note& N);
};

#endif /* PluriNotes_h */
