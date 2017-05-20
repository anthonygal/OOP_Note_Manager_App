#ifndef PluriNotes_h
#define PluriNotes_h

#include <iostream>
#include <string>
#include "timing.h"


enum NoteEtat{ active, archivee, corbeille };
enum TacheStatut{ attente, encours, terminee };
enum TypeMultimedia{ image, video, audio };


class Note{
private:
    int ID;
    std::string Titre;
    TIME::Date DateCrea;
    TIME::Date DateModif;
    NoteEtat Etat;
    bool Actuel;
    virtual void estAbstraite()=0;
public:
    Note(const std::string&);
    virtual ~Note();
};

/*
 COMMENTAIRES A PRENDRE EN COMPTE:
    -Pour la gestion des type dates horaire etc... on reprendra les fichiers timing.h et timing.cpp donnés en ressources lors du TD7
    -Les accesseurs en edition créeent la nouvelle version de la note prenant les modifications souhaitées en compte et renvoyeent l'addresse de la nouvelle version de la note créer
    -La seule utilité de la methode virtuelle pure estAbstraite() est de rendre la classe Note abstraite. Son comportement (ne fait rien du tout) est défini dans les sous classe afin de rendre ces sous classes concrètes. Cette fonction pourra ne sera plus necessaire si une methode virtuelle pure utile vient à etre implementée plus tard



 */

class Article: public Note{
private:
    std::string Texte;
    virtual void estAbstraite(){};

public:
    std::string getTexte() const;
    Article& setTexte(const std::string& t);

    Article(const std::string& titre, const std::string& texte="");
};


class Tache: public Note{
private:
    std::string Action;
    TacheStatut Statut;
    int Priorite;
    TIME::Date Echeance;
    virtual void estAbstraite(){};

public:
    std::string getAction() const {return Action;};
    int getPriorite() const {return Priorite;};
    TIME::Date getEcheance() const {return Echeance;};
    Tache& setAction(const std::string& s);
    Tache& setPriorite(int p);
    Tache& setEcheance(const TIME::Date& d);

    Tache(const std::string& titre, const std::string& action, int priority=0);
};


class Multimedia: public Note{
private:
    std::string AdresseFichierImage;
    std::string Description;
    TypeMultimedia Type;
    virtual void estAbstraite(){};

public:
    std::string getAdresseFichierImage() const {return AdresseFichierImage;}
    std::string getDescription() const {return Description;};
    TypeMultimedia getTypeMultimedia() const {return Type;};
    Multimedia& setAdresseFichierImage(const std::string& f);
    Multimedia& setDescription(const std::string& d);
    Multimedia& setTypeMultimedia(const TypeMultimedia t);

    Multimedia(const std::string& titre, const std::string adressefichierimage, const std::string Description="", TypeMultimedia T=image);
};








#endif /* PluriNotes_h */
