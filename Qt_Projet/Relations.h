#ifndef Relations_hpp
#define Relations_hpp

#include "PluriNotes.h"
#include <QString>

using namespace TIME;

 /**< RELATIONS ENTRE NOTES */

class Note;
class Manager;
class NoteException;

/**< CLASS COUPLE */
class Couple{
private:
    QString label;
    Note* note1;
    Note* note2;
public:
    /**< Constructeur */
    Couple(Note* A, Note* B, QString l):label(l),note1(A),note2(B){};
    /**< Requetes getAttributs */
    QString getLabel() const {return label;}
    Note* getNote1() const {return note1;}
    Note* getNote2() const {return note2;}
    /**< Commandes setAttributs */
    void setLabel(const QString& s){label=s;}
    void setNotes1(Note* n){note1=n;}
    void setNotes2(Note* n){note2=n;}
};

/**< CLASS RELATION */
class Relation{
private:
    QString titre;
    QString description;
    bool orientee;
    Couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
public:
    /**< Constructeur */
    Relation(const QString& t, const QString& d, bool o=true);
    /**< Destructeur */
    virtual ~Relation();
    /**< Requetes getAttributs */
    QString getTitre() const {return titre;}
    QString getDescription() const {return description;}
    bool getOrientee() const {return orientee;}
    Couple** getCouples() const {return couples;}
    int getnbCouples() const {return nbCouples;}
    /**< Commandes setAttributs */
    void setOrientatee(){orientee=true;}
    void setNonOrientatee(){orientee=false;}
    /**< Methode pour ajouter un couple a la relation */
    void addCouple(Couple& c);
};

/**< CLASS REFERENCE FILLE DE RELATION */
class Reference: public Relation {
private:
    /**< Template Method Singleton */
    static Reference* instanceUnique;
    /**< Constructeur */
    Reference():Relation("Reference","Note1 fait reference à Note2", true){};
    Reference(const Reference& R);
    void operator=(const Reference& R);
    /**< Destructeur */
    ~Reference();
 public:
    /**< Template Method Singleton */
    static Reference& donneInstance();
    static void libereInstance();
 };

/**< Je te laisse Anthony ^^ */
unsigned long findRefID(const QString& s, int p);

int getPosition(const QString& s, int p);

#endif /* Relations_h */
