#ifndef PluriNotes_h
#define PluriNotes_h

#include <string>
#include "timing.h"

using namespace TIME;

enum NoteEtat{ active, archivee, corbeille };
enum TacheStatut{ attente, encours, terminee };
enum TypeMultimedia{ image, video, audio };

class Note{
private:
    int ID;
    std::string titre;
    TIME::Date dateCrea;
    TIME::Date dateModif;
    TIME::Horaire horaireCrea;
    TIME::Horaire horaireModif;
    NoteEtat etat;
    bool actuel;
    //virtual void estAbstraite()=0;
public:
    Note(const std::string& s): titre(s), dateCrea(dateNow()), dateModif(dateNow()), horaireCrea(horaireNow()), horaireModif(horaireNow()), etat(active), actuel(true){};//Pas besoin d'initialiser horaire et tout, sont initialiser à la construction
//    Note(const Note& n){
//        titre = n.titre;
//        dateCrea= n.dateCrea;
//        horaireCrea=n.horaireCrea;
//        actuel=n.actuel;
//        n.setactuel(false);
//    }
    const std::string gettitre() const {return titre; }
    const Date& getdateCrea() const {return dateCrea;}
    const Date& getdateModif() const {return dateModif;} //Laisser ou enlever le const? La date de modif est ammenée à être modifié, mais on créera alors une nouvelle notes
    const Horaire& gethoraireCrea() const {return horaireCrea;}
    const Horaire& gethoraireModif() const {return horaireModif;}
    NoteEtat getetat() const {return etat;} //0 pour active, 1 pour archivee et 2 pour corbeille
    bool getactuel () const {return actuel;}
    void setactuel (bool f){actuel=f; }

   // virtual ~Note();
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
    virtual void estAbstraite(){};

public:
    Article(const std::string& titre, const std::string& texte="");


    std::string getTexte() const;
    Article& setTexte(const std::string& t);

    Article();
};


class Tache: public Note{
private:
    std::string action;
    TacheStatut statut;
    int priorite;
    TIME::Date echeance;
    virtual void estAbstraite(){};

public:
    std::string getAction() const {return action;};
    int getPriorite() const {return priorite;};
    TIME::Date getEcheance() const {return echeance;};
    Tache& setAction(const std::string& s);
    Tache& setPriorite(int p);
    Tache& setEcheance(const TIME::Date& d);

    Tache(const std::string& titre, const std::string& action, int priority=0);
};


class Multimedia: public Note{
private:
    std::string adresseFichierImage;
    std::string description;
    TypeMultimedia type;
    virtual void estAbstraite(){};

public:
    std::string getAdresseFichierImage() const {return adresseFichierImage;}
    std::string getDescription() const {return description;};
    TypeMultimedia getTypeMultimedia() const {return type;};
    Multimedia& setAdresseFichierImage(const std::string& f);
    Multimedia& setDescription(const std::string& d);
    Multimedia& setTypeMultimedia(const TypeMultimedia t);

    Multimedia(const std::string& titre, const std::string adressefichierimage, const std::string Description="", TypeMultimedia T=image);
};




#endif /* PluriNotes_h */
