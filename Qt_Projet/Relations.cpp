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


// Fonction qui trouve dans tout string en partant de la position p si il y a une reference, dans ce cas, renvoie son ID, sinon, renvoie 0

unsigned long findRefID(const QString& s, int p){

    int l=s.length();
    QStringRef r=QStringRef(&s,p,l-p);
    int i=s.indexOf("\ref{")+4;
    int j= i;
    if (i!=-1){
    QChar c;
   c=r.at(i);
   if (!c.isDigit()) return -1;
    int idlength=0;
    while (c!='}' && i<l-p) {
       idlength++;
        if (!c.isDigit()) return -1;
        i++;
        c=r.at(i);
    }
    if(i==l-p) return -1;
    else{
        QString f=r.toString();
        QStringRef x=QStringRef(&f,j,idlength);
        int id=x.toInt();
        return id;
        }
    }
    return -1;
}


/*
unsigned long findRefID(const std::string& s, int p){

    unsigned long i=s.find("ref{", p);

    if(i==p) return 0;
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
            unsigned long id;
            t>>id;
            if (c=='}') return id;
            else return 0;
        }
    }
}*/

//Fonction qui renvoie la position du "}" fermant la reference à partir de la position p passé en argument si une reference existe dans le string s, sinon renvoie 0

int getPosition(const QString& s, int p){

    int l=s.length();
    QStringRef r=QStringRef(&s,p,l-p);
    unsigned int i=s.indexOf("\ref{")+4;
    unsigned int j= i;
    if (i!=-1){

    QChar c=r.at(i);
    if (!c.isDigit()) return -1;
    int idlength=0;
    while (c!='}' && i<l-p) {
        idlength++;
        if (!c.isDigit()) return -1;
        i++;
        c=r.at(i);
    }
    if(i==l-p) return -1;
    else return p+j+idlength+3;
    }

    return -1;
}
/*
int getPosition(const std::string s, int p){
    int i=s.find("ref{", p);
    if (i==p) return 0;
    else {
        i+=4;
        char c=s[i];
        if (!isdigit(c)) {return 0;}
        else{
            while (isdigit(c)){
                i++;
                c=s[i];
            }
            if (c=='}') return i;
            else return 0;
        }
    }

}
*/



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
