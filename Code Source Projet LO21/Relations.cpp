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

// Fonction qui trouve dans tout string si il y a une reference, dans ce cas, renvoie son ID, sinon, renvoie 0
int findRefID(const std::string& s){
    
    unsigned long i=s.find("ref{", 0);
    if (i==0) return 0;
    else {
        i+=4;
        char c=s[i];
        if (!isdigit(c)) {return 0;}
        else{
            std::stringstream t;
            while (isdigit(c)){
                t<<c;
                i++;
                c=s[i];
            }
            unsigned int id;
            t>>id;
            if (c=='}') return id;
            else return 0;
        }
    }
}
