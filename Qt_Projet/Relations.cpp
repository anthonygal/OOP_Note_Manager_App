#include "Relations.h"
#include "Manager.h"

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

void Relation::saveRelation(QXmlStreamWriter& stream)const{
    stream.writeStartElement("relations");
    stream.writeTextElement("titre", titre);
    stream.writeTextElement("description",description);
    stream.writeTextElement("orientee", Manager::booltoQString(orientee));
    for(unsigned int j=0; j<nbCouples;j++){
        couples[j]->saveCouple(stream);
    }
    stream.writeEndElement();
}

void Couple::saveCouple(QXmlStreamWriter& stream) const{
    stream.writeStartElement("couples");
    stream.writeTextElement("label", label);
    stream.writeTextElement("ID1",QString::number(ID1));
    stream.writeTextElement("ID2",QString::number(ID2));
    stream.writeEndElement();
}
