#include "PluriNotes.h"

//Appel des constructeur par recopie => sera utilisé lors du design Pattern Factory method plus tard
Article* Article::clone() const{
return new Article(*this);
};

Tache* Tache::clone() const{
return new Tache(*this);
};

Multimedia* Multimedia::clone() const{
return new Multimedia(*this)};
