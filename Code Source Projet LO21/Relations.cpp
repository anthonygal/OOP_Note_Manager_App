#include "Relations.h"

// RELATIONS ENTRE NOTES


Relation::Relation(const std::string& t, const std::string& d, bool o){
    titre=t;
    description=d;
    orientation=o;
    couples=new Couple*[100];
};

Relation::~Relation(){
    for(unsigned int i = 0; i<nbCouples;i++){
        delete couples[i];}
    delete[] couples;}

void Relation::addCouple(Couple& c){
    if (nbCouples==nbMaxCouples){
        Couple** newtab= new Couple* [nbMaxCouples+100];
        for(int i=0; i<nbCouples;i++){
            newtab[i]=couples[i];
        }
        nbCouples=nbCouples+100;
        Couple** oldtab= couples;
        couples=newtab;
        delete [] oldtab;
    }
    couples[nbCouples]=&c;
    nbCouples++;
}


