#include "PluriNotes.h"

void Note::afficher() const {
    std::cout<<"\nID : "<<ID<<"\nTitre : "<<titre<<"\nCree le : "<<dateCrea<<" a "<<horaireCrea<<"\nModifie le "<<dateModif<<" a "<<horaireModif<<"\nEtat : "<<etat<<(actuel?"\nVersion Actuelle\n":"\nVersion Ancienne\n");
}
