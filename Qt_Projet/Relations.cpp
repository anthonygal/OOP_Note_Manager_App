#include "Relations.h"

// RELATIONS ENTRE NOTES

Relation::Relation(const QString& t, const QString& d, bool o){
    titre=t;
    description=d;
    orientee=o;
    couples=new Couple*[5];
    nbCouples=0;
    nbMaxCouples=5;
};

Relation::~Relation(){
    for(unsigned int i=0; i<nbCouples;i++){
        delete couples[i];}
    delete[] couples;
}

void Relation::addCouple(Couple& c){
    if (nbCouples==nbMaxCouples){
        Couple** newtab= new Couple* [nbMaxCouples+5];
        for(unsigned int i=0; i<nbCouples;i++){
            newtab[i]=couples[i];
        }

        //nbMaxCouples=nbMaxCouples+100; //Changement Antoine
        nbCouples=nbCouples+5; //Changement Antho

        Couple** oldtab= couples;
        couples=newtab;
        delete [] oldtab;
    }
    couples[nbCouples]=&c;
    nbCouples++;
}

Reference::~Reference(){
    this->Relation::~Relation();
}

//Singleton de la classe REFERENCE

Reference* Reference::instanceUnique=nullptr;
Reference& Reference::donneInstance(){
    if (instanceUnique==nullptr) instanceUnique= new Reference();
    return *instanceUnique;
}
void Reference::libereInstance(){
    if (instanceUnique!=0) delete instanceUnique;
    instanceUnique=nullptr;
}
