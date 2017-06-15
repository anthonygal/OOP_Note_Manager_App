#ifndef Notes_h
#define Notes_h

//#include "timing.h"
#include <string>
#include <typeinfo>
#include <sstream>
#include <QtXml>
#include <QXmlStreamWriter>
#include <QString>
#include <QtWidgets>
#include <QFile>

const QString formatDate = "dd/MM/yyyy";
const QString formatDateTime = "dd/MM/yyyy HH:mm:ss";

enum NoteEtat{ active, archivee, corbeille }; /**< Les differents etats d'une Note */
enum TacheStatut{ attente, encours, terminee }; /**< Les differents statuts d'une Tache */
enum TypeMultimedia{ image, video, audio }; /**< Les differents types de fichier Multimedia */

class Relation;
class Couple;
class Reference;
class Manager;
class NoteEditeur;
class ArticleEditeur;
class TacheEditeur;
class MultimediaEditeur;

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
    unsigned long ID;
    QString titre;
    QDateTime dateCrea;
    QDateTime dateModif;
    NoteEtat etat;
    bool actuelle;
public:
    /**< Constructeurs */
    Note(const unsigned long i, const QString& s): ID(i),titre(s), dateCrea(QDateTime::currentDateTime()), dateModif(QDateTime::currentDateTime()), etat(active), actuelle(true){}
    Note(const unsigned long i, const QString& s, const QDateTime& dc, const QDateTime& dm, bool act, NoteEtat e): ID(i), titre(s), dateCrea(dc), dateModif(dm), etat(e), actuelle(act){}
    Note(Note& n);
    /**< Destructeur */
    virtual ~Note(){}
    /**< Requetes getAttributs */
    unsigned long getID() const {return ID;}
    QString getTitre() const {return titre;}
    const QDateTime& getDateCrea() const {return dateCrea;}
    const QDateTime& getDateModif() const {return dateModif;}
    NoteEtat getEtat() const {return etat;} /**< etat vaut 0 pour active, 1 pour archivee et 2 pour corbeille */
    bool isActuelle() const {return actuelle;}
    virtual QString getTypeNote() const = 0;
    /** Methodes permettant de passer des attributs en QString */
    QString NoteEtattoQString()const;
    //QString ActuelletoQString()const;
    /** Methodes permettant de passer des QString en attributs */
    static NoteEtat QStringtoNoteEtat(const QString& str);
    //static bool QStringtoActuel(const QString & str);
    /**< Commandes setAttributs */
    void setTitre(const QString ti){titre=ti;}
    void setEtat(NoteEtat e){etat=e;}
    void setActuelle(){actuelle=true;}
    void setAncienne(){actuelle=false;}
    /**< Methode d'edition */
    virtual void edit() = 0;
    /**< Methodes pour ajouter des references */
    void addRefs() const;
    virtual void addRefsSpecifique() const=0;
    /** Methode virtuelle pure permettant de sauvegarder dans un fichier xml une note particuliere */
    void saveNote(QXmlStreamWriter& stream)const;
    virtual void saveNoteSpecifique(QXmlStreamWriter& stream)const=0;
};

/**< CLASSE ARTICLE FILLE DE NOTE */
class Article: public Note{
    QString texte;
public:
    /**< Constructeurs d'Article */
    Article(const unsigned long i, const QString& ti, const QString& te=""):Note(i,ti),texte(te){}
    Article(const unsigned long i, const QString& s, const QDateTime& dc, const QDateTime& dm, bool act, NoteEtat e, const QString& te):Note(i,s,dc,dm,act,e), texte(te){}
    Article(Article& a):Note(a),texte(a.texte){}
    /**< Destructeur d'Article */
    ~Article(){}
    /**< Requetes getAttributs */
    QString getTexte() const {return texte;}
    QString getTypeNote() const {return "Article";}
    /**< Commandes setAttributs */
    void setTexte(const QString& t){texte=t;}
    /**< Methode d'edition */
    void edit();
    /**< Methode pour ajouter des references specifique */
    void addRefsSpecifique() const;
    /** Methode permettant de sauvegarder dans un fichier xml une note particuliere */
    void saveNoteSpecifique(QXmlStreamWriter& stream)const;
};

/**< CLASSE TACHE FILLE DE NOTE */
class Tache: public Note{
    QString action;
    int priorite;
    QDate echeance;
    TacheStatut statut;
public:
    /**< Constructeurs de Tache */
    Tache(const unsigned long i, const QString& ti, const QString& act, int prio=0, const QDate& d=QDate()):Note(i,ti),action(act),priorite(prio),echeance(d),statut(encours){}
    Tache(const unsigned long i, const QString& s, const QDateTime& dc, const QDateTime& dm, bool act, NoteEtat e, const QString& acti, const int prio, const QDate& eche, const TacheStatut ts)
        :Note(i,s,dc,dm,act,e),action(acti),priorite(prio),echeance(eche), statut(ts){}
    Tache(Tache& t):Note(t),action(t.action),priorite(t.priorite),echeance(t.echeance),statut(t.statut){}
    /**< Destructeur de Tache */
    ~Tache(){}
    /**< Requetes getAttributs */
    QString getAction() const {return action;}
    TacheStatut getStatut() const {return statut;}
    int getPriorite() const {return priorite;}
    QDate getEcheance() const {return echeance;}
    QString getTypeNote() const {return "Tache";}
    /** Methodes permettant de passer des attributs en QString */
    QString TacheStatuttoQString()const;
    /** Methodes permettant de passer des QString en attributs */
    static TacheStatut QStringtoTacheStatut(const QString & str);
    /**< Commandes setAttributs */
    void setAction(const QString& act){action=act;}
    void setStatut(const TacheStatut s){statut=s;}
    void setPriorite(int p){priorite=p;}
    void setEcheance(const QDate& d){echeance=d;}
    /**< Methode d'edition */
    void edit();
    /**< Methode pour ajouter des references specifique */
    void addRefsSpecifique() const;
    /** Methode permettant de sauvegarder dans un fichier xml une note particuliere */
    void saveNoteSpecifique(QXmlStreamWriter& stream)const;
};

/**< CLASSE MULTIMEDIA FILLE DE NOTE */
class Multimedia: public Note{
    QString adresseFichier;
    TypeMultimedia type;
    QString description;
public:
    /**< Constructeurs de Multimedia */
    Multimedia(const unsigned long i, const QString& ti, const QString& adr, TypeMultimedia ty=image, const QString& desc=""):Note(i,ti),adresseFichier(adr),type(ty),description(desc){}
    Multimedia(Multimedia& m):Note(m),adresseFichier(m.adresseFichier),type(m.type),description(m.description){}
    Multimedia(const unsigned long i, const QString& s, const QDateTime& dc, const QDateTime& dm, bool act, NoteEtat e, const QString& af, const TypeMultimedia ty,const QString& dec):Note(i,s,dc,dm,act,e),adresseFichier(af), type(ty), description(dec){}
    /**< Destructeur de Multimedia */
    ~Multimedia(){}
    /**< Requetes getAttributs */
    QString getAdresseFichier() const {return adresseFichier;}
    QString getDescription() const {return description;}
    TypeMultimedia getType() const {return type;}
    QString getTypeNote() const {return "Multimedia";}
    /** Methodes permettant de passer des attributs en QString */
    QString TypeMultimediatoQString()const;
    /** Methodes permettant de passer des QString en attributs */
    static TypeMultimedia QStringtoTypeMultimedia(const QString & str);
    /**< Commandes setAttributs */
    void setAdresseFichier(const QString& adr){adresseFichier=adr;}
    void setDescription(const QString& desc){description=desc;}
    void setType(const TypeMultimedia ty){type=ty;}
    /**< Methode d'edition */
    void edit();
    /**< Methode pour ajouter des references specifique */
    void addRefsSpecifique() const;
    /** Methode permettant de sauvegarder dans un fichier xml une note particuliere */
    void saveNoteSpecifique(QXmlStreamWriter& stream)const;
};

/**< Je te laisse Anthony ^^ */
long findRefID(const QString& s, int p);
int getPosition(const QString& s, int p);

#endif /* Notes_h */
