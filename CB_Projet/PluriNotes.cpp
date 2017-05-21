#include "PluriNotes.h"

//Appel des constructeur par recopie => sera utilisé lors du design Pattern Factory method plus tard
Article* Article::clone() {
return new Article(*this);
};

Tache* Tache::clone() {
return new Tache(*this);
};

Multimedia* Multimedia::clone() {
return new Multimedia(*this);};

Note::Note(Note& n){
        titre = n.titre;
        dateCrea= n.dateCrea;
        horaireCrea=n.horaireCrea;
        actuel=n.actuel;
        n.setactuel(false);
        dateModif = TIME::dateNow();
        horaireModif = TIME::horaireNow();
    }
