#include "Relations.h"

// RELATIONS ENTRE NOTES

/**< TEMPLATE METHOD ITERATOR DANS LA CLASSE RELATION POUR LES COUPLES */

void Relation::IteratorCouples::next(){
    if(isDone()) throw NoteException("\nnext() sur un IteratorCouple fini !\n");
    remain--;
    currentC++;
}

Couple& Relation::IteratorCouples::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un IteratorCouple fini !\n");
    return **currentC;
}

Relation::~Relation(){
    for(unsigned int i=0; i<nbCouples;i++)
        delete couples[i];
    delete[] couples;
}

void Relation::addCouple(unsigned int id1, unsigned int id2, const QString &lab){
    if (nbCouples==nbMaxCouples){
        Couple** newtab= new Couple*[nbMaxCouples+5];
        for(unsigned int i=0; i<nbCouples;i++){
            newtab[i]=couples[i];
        }
        nbMaxCouples=nbMaxCouples+5;
        Couple** oldtab = couples;
        couples = newtab;
        delete[] oldtab;
    }
    couples[nbCouples++]= new Couple(id1,id2,lab);
}

//Singleton de la classe REFERENCE

Reference* Reference::instanceUnique=nullptr;

Reference& Reference::donneInstance(){
    if (instanceUnique==nullptr) instanceUnique= new Reference;
    return *instanceUnique;
}

void Reference::libereInstance(){
    if (instanceUnique!=0) delete instanceUnique;
    instanceUnique=nullptr;
}
