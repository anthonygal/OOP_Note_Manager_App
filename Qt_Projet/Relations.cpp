#include "Relations.h"
#include "Manager.h"

// RELATIONS ENTRE NOTES

/**< Iterator de couples */

void Relation::IteratorCouples::next(){
    if(isDone()) throw NoteException("\nnext() sur un IteratorCouple fini !\n");
    remain--;
    currentC++;
}

Couple& Relation::IteratorCouples::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un IteratorCouple fini !\n");
    return **currentC;
}

/**< ConstIterator de couples */

void Relation::ConstIteratorCouples::next(){
    if(isDone()) throw NoteException("\nnext() sur un ConstIteratorCouple fini !\n");
    remain--;
    currentC++;
}

const Couple& Relation::ConstIteratorCouples::current() const{
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

//Passer en iterateur?
void Relation::supprimerCouple(Couple& c){
    for(unsigned int i=0; i<nbCouples; i++){
        if(couples[i]==&c){     //On cherche si le couple existe bien dans la relation
            Couple* temp=couples[i];
            for(unsigned int j=i; j<nbCouples-1;j++){ //on sort le couple du tableau
                couples[j]=couples[j+1];
            }
            delete temp;    //On detruit le couple
            nbCouples--;    //On met a jour le nombre de couples dans la relation
            i--;
        }
    }
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

void Relation::saveRelation(QXmlStreamWriter& stream) const {
    stream.writeStartElement("Relation");
    stream.writeTextElement("titre", titre);
    stream.writeTextElement("description",description);
    stream.writeTextElement("orientee", Manager::booltoQString(orientee));
    for(ConstIteratorCouples it=getConstIteratorCouples(); !it.isDone(); it.next()){
        it.current().saveCouple(stream);
    }
    stream.writeEndElement();
}

void Couple::saveCouple(QXmlStreamWriter& stream) const{
    stream.writeStartElement("couple");
    stream.writeTextElement("label", label);
    stream.writeTextElement("ID1",QString::number(ID1));
    stream.writeTextElement("ID2",QString::number(ID2));
    stream.writeEndElement();
}

//void Reference::saveReference(QXmlStreamWriter& stream){
//    stream.writeStartElement("references");
//    stream.writeTextElement("titre", getTitre());
//    stream.writeTextElement("description",getDescription());
//    stream.writeTextElement("orientee",orienteetoQString());
//    for(unsigned int j=0; j<nbCouples;j++){
//        couples[j]->savecouple(stream);
//    }
//}

