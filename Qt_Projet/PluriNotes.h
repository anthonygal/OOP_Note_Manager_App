#ifndef PluriNotes_h
#define PluriNotes_h

#include "timing.h"
#include "Relations.h"
#include <string>
#include <typeinfo>
#include <sstream>
#include <QtXml>
#include <QXmlStreamWriter>
#include <QString>

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
    QString info;
public:
    NoteException(const QString& s): info(s){}
    QString getInfo() const {return info;}
};

/**< CLASSE ABSTRAITE NOTE */
class Note{
private:
    unsigned long ID;
    QString titre;
    TIME::Date dateCrea;
    TIME::Horaire horaireCrea;
    TIME::Date dateModif;
    TIME::Horaire horaireModif;
    NoteEtat etat;
    bool actuel;
public:
    /**< Constructeurs */
    Note(const unsigned long i, const QString& s): ID(i),titre(s), dateCrea(dateNow()), horaireCrea(horaireNow()), dateModif(dateNow()), horaireModif(horaireNow()), etat(active), actuel(true){}
    Note(const unsigned long i, const QString& s, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e): ID(i), titre(s), dateCrea(dc), horaireCrea(hc),
        dateModif(dm), horaireModif(hm), actuel(act),etat(e){}
    
    Note(Note& n);
    /**< Destructeur */
    virtual ~Note(){};
    /**< Requetes getAttributs */
    unsigned long getID() const {return ID;}
    QString getTitre() const {return titre;}
    const Date& getDateCrea() const {return dateCrea;} //Pourquoi Date et Horaire doivent passer un const contrairement a string ou autre type?
    const Date& getDateModif() const {return dateModif;}
    const Horaire& getHoraireCrea() const {return horaireCrea;}
    const Horaire& getHoraireModif() const {return horaireModif;}
    NoteEtat getEtat() const {return etat;} /**< etat vaut 0 pour active, 1 pour archivee et 2 pour corbeille */
    bool getActuel() const {return actuel;}
    /**< Commandes setAttributs */
    void setTitre(const QString ti){titre=ti;}
    void setEtat(NoteEtat e){etat=e;}
    void setActuel(){actuel=true;}
    void setAncienne(){actuel=false;}
    /**< Methode d'edition */
   //virtual Note& edit()=0;
    /**< Methodes d'affichage */
   // void afficher(std::ostream& f = std::cout) const;
   // virtual void afficherSpecifique(std::ostream& f) const = 0;
    /**< Methodes pour ajouter des references */
    void AddRefs(Manager& m);
    virtual void AddRefsSpecifique(Manager& m)=0;

    virtual void saveNote(QXmlStreamWriter& stream)const=0;
    QString NoteEtattoQString()const;
    static NoteEtat QStringtoNoteEtat(const QString& str);
    QString ActueltoQString()const;
    static bool QStringtoActuel(const QString & str);
};

/**< Surcharge de l'operateur << pour afficher une note avec ce dernier */
std::ostream& operator<<(std::ostream& f , const Note& n);

/**< CLASSE ARTICLE FILLE DE NOTE */
class Article: public Note{
private:
    QString texte;
public:
    /**< Constructeurs d'Article */
    Article(const unsigned long i, const QString& ti, const QString& te=""):Note(i,ti),texte(te){}
    Article(const unsigned long i, const QString& s, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e, const QString& te):Note(i,s,dc,hc,dm,hm,act,e), texte(te){}
    Article(Article& a):Note(a),texte(a.texte){}
    /**< Destructeur d'Article */
    ~Article(){}
    /**< Requetes getAttributs */
    QString getTexte() const{return texte;}
    /**< Commandes setAttributs */
    void setTexte(const QString& t){texte=t;}
    /**< Methode d'edition */
    Article& edit();
    /**< Methode d'affichage specifique */
   // void afficherSpecifique(std::ostream& f) const;
    /**< Methode pour ajouter des references specifique */
    void AddRefsSpecifique(Manager& m);

    void saveNote(QXmlStreamWriter& stream)const;

};

/**< CLASSE TACHE FILLE DE NOTE */
class Tache: public Note{
private:
    QString action;
    int priorite;
    TIME::Date echeance;
    TacheStatut statut;
public:
    /**< Constructeurs de Tache */
    Tache(const unsigned long i, const QString& ti, const QString& act, int prio=0, Date d=Date(1,1,0)):Note(i,ti),action(act),priorite(prio),echeance(d),statut(encours){}
    Tache(const unsigned long i, const QString& s, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e, const QString& acti, const int prio, const Date eche, const TacheStatut ts)
        :Note(i,s,dc,hc,dm,hm,act,e),action(acti),priorite(prio),echeance(eche), statut(ts){}
    Tache(Tache& t):Note(t),action(t.action),priorite(t.priorite),echeance(t.echeance),statut(t.statut){}
    /**< Destructeur de Tache */
    ~Tache(){}
    /**< Requetes getAttributs */
    QString getAction() const {return action;}
    TacheStatut getStatut() const {return statut;}
    int getPriorite() const {return priorite;}
    TIME::Date getEcheance() const {return echeance;}
    /**< Commandes setAttributs */
    void setAction(const QString& act){action=act;}
    void setStatut(const TacheStatut s){statut=s;}
    void setPriorite(int p){priorite=p;}
    void setEcheance(const TIME::Date& d){echeance=d;}
    /**< Methode d'edition */
    Tache& edit();
    /**< Methode d'affichage specifique */
    //void afficherSpecifique(std::ostream& f) const;
    /**< Methode pour ajouter des references specifique */
    void AddRefsSpecifique(Manager& m);

    void saveNote(QXmlStreamWriter& stream)const;
    void loadTache();
    QString TacheStatuttoQString()const;
    static TacheStatut QStringtoTacheStatut(const QString & str);
};

/**< CLASSE MULTIMEDIA FILLE DE NOTE */
class Multimedia: public Note{
private:
    QString adresseFichier;
    TypeMultimedia type;
    QString description;
public:
    /**< Constructeurs de Multimedia */
    Multimedia(const unsigned long i, const QString& ti, const QString& adr, TypeMultimedia ty=image, const QString& desc=""):Note(i,ti),adresseFichier(adr),type(ty),description(desc){}
    Multimedia(Multimedia& m):Note(m),adresseFichier(m.adresseFichier),type(m.type),description(m.description){}
    Multimedia(const unsigned long i, const QString& s, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e, const QString& af, const TypeMultimedia ty,const QString& dec):Note(i,s,dc,hc,dm,hm,act,e),adresseFichier(af), type(ty), description(dec){}

    /**< Destructeur de Multimedia */
    ~Multimedia(){}
    /**< Requetes getAttributs */
    QString getAdresseFichier() const {return adresseFichier;}
    QString getDescription() const {return description;}
    TypeMultimedia getType() const {return type;}
    /**< Commandes setAttributs */
    void setAdresseFichier(const QString& adr){adresseFichier=adr;}
    void setDescription(const QString& desc){description=desc;}
    void setType(const TypeMultimedia ty){type=ty;}
    /**< Methode d'edition */
    Multimedia& edit();
    /**< Methode d'affichage specifique */
   // void afficherSpecifique(std::ostream& f) const;
    /**< Methode pour ajouter des references specifique */
    void AddRefsSpecifique(Manager& m);

    void saveNote(QXmlStreamWriter& stream)const;
    void loadMultimedia();
    QString TypeMultimediatoQString()const;
    static TypeMultimedia QStringtoTypeMultimedia(const QString & str);
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
    mutable QString filename;
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
    Reference& getReference();
    Note* searchID(unsigned long id);
    /**< Methode pour afficher toutes les notes */
    void afficherTout() const;
    /**< Methodes pour ajouter un Article/Tache/Multimedia au tableau de notes*/
    void newArticle(const QString& ti, const QString& te=""); /**< creation d'un article */
    void newTache(const QString& ti, const QString& act, int prio=0, Date d=Date(1,1,0)); /**< creation d'une tache */
    void newMultimedia(const QString& ti, const QString& adr, const QString& desc="", TypeMultimedia ty=image); /**< creation d'un multimedia */
    /**< Methode pour editer une note */
    void editNote(Note& n);
    /**< Methodes d'edition inutiles pour l'instant mais je prefere garder au cas ou */
    Article& editTexteArticle(Article& A, const QString& s);
    Tache& editActionTache(Tache& T, const QString& s);
    Tache& editStatutTache(Tache& T, TacheStatut s);
    Tache& editPrioriteTache(Tache& T, int p);
    Tache& editEcheanceTache(Tache& T, TIME::Date d);
    Multimedia& editFichierMultimedia(Multimedia& M, const QString s);
    /**< Methodes d'ajout de Relation/Reference */
   void addRelation(Relation& r);
  void addCoupleRelation(Relation& r, Couple& c);
  void addCoupleReference(Couple& c);
    void AddRefsFromNote(Note& N);
    //Methode permettant de savoir si une note est referencee
    bool isReferenced(const Note& N) const;
    //Supression ou Archivage de Note
    void supprimer(Note& N);
    void viderCorbeille();

    void save()const;
    void load();
    //void loadArticle();
    //void loadTache();
    //void loadMultimedia();
    void addArticle(const int id, const QString& ti, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e,const QString& te );
    void addTache(const int id, const QString& ti, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e,const QString& acti, const int prio, const Date eche, const TacheStatut ts );
    void addMultimedia(const int id, const QString& ti, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e,const QString& af, const TypeMultimedia ty,const QString& dec);


    void setFilename(const QString& f) { filename=f; }
};

#endif /* PluriNotes_h */
