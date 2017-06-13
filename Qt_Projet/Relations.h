#ifndef Relations_hpp
#define Relations_hpp

#include "Notes.h"

using namespace TIME;

 /**< RELATIONS ENTRE NOTES */

class Note;
class Manager;
class NoteException;

/**< CLASS COUPLE */
class Couple{
    friend class Relation;
    QString label;
    unsigned int ID1;
    unsigned int ID2;
    /**< Constructeur */
    Couple(unsigned int id1, unsigned int id2, const QString& l):label(l),ID1(id1),ID2(id2){}
public:
    /**< Requetes getAttributs */
    QString getLabel() const {return label;}
    unsigned int getID1() const {return ID1;}
    unsigned int getID2() const {return ID2;}
    /**< Commandes setAttributs */
    void setLabel(const QString& s){label=s;}
    void saveCouple(QXmlStreamWriter& stream) const;
};

/**< CLASS RELATION */
class Relation{
    QString titre;
    QString description;
    bool orientee;
    Couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
public:
    /**< Constructeur */
    Relation(const QString& t, const QString& d, bool o=true):titre(t), description(d), orientee(o), couples(new Couple*[5]), nbCouples(0),nbMaxCouples(5){}
    /**< Destructeur */
    virtual ~Relation();
    /**< Requetes getAttributs */
    QString getTitre() const {return titre;}
    QString getDescription() const {return description;}
    bool isOrientee() const {return orientee;}
    Couple** getCouples() const {return couples;}
    int getnbCouples() const {return nbCouples;}
    int getnbMaxCouples() const {return nbMaxCouples;}
    /**< Commandes setAttributs */
    void setOrientee(){orientee=true;}
    void setNonOrientee(){orientee=false;}
    /**< Iterateur de couples */
    class IteratorCouples{
    private:
        friend class Relation;
        Couple** currentC;
        int remain;
        IteratorCouples(Couple** t, int n): currentC(t), remain(n){}
    public:
        bool isDone() const {return !remain;}
        void next();
        Couple& current() const;
    };
    IteratorCouples getIteratorCouples() const {return IteratorCouples(couples, nbCouples);}
    /**< Methode pour ajouter un couple a la relation */
    void addCouple(unsigned int id1, unsigned int id2, const QString& lab);
    void supprimerCouple(Couple& c);
    void saveRelation(QXmlStreamWriter& stream)const;
};

/**< CLASS REFERENCE FILLE DE RELATION */
class Reference: public Relation {
private:
    /**< Template Method Singleton */
    static Reference* instanceUnique;
    /**< Constructeurs */
    Reference():Relation("Reference","Note1 fait reference à Note2", true){}
    Reference(const Reference& R);
    void operator=(const Reference& R);
    /**< Destructeur */
    ~Reference(){}
 public:
    /**< Template Method Singleton */
    static Reference& donneInstance();
    static void libereInstance();
    void saveReference(QXmlStreamWriter& stream)const;
 };

#endif /* Relations_h */
