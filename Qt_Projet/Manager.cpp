#include "Manager.h"

/*
void Manager::afficherTout()const{
    for(ConstIteratorNotes it=getConstIteratorNotes();!it.isDone();it.next()) std::cout<<it.current()<<std::endl;
}
*/

/**< TEMPLATE METHOD SINGLETON POUR LA CLASS MANAGER */

Manager* Manager::InstanceUnique=nullptr;

Manager& Manager::donneInstance(){
    if (InstanceUnique==nullptr) InstanceUnique = new Manager;
    return *InstanceUnique;
}

void Manager::libereInstance(){
    if (InstanceUnique!=nullptr)
        delete InstanceUnique;
    InstanceUnique=nullptr;
}

Manager::~Manager(){

    for(unsigned int i = 0; i<nbNotes;i++){
        delete notes[i]; //un destructeur virtuel pour Note à definir à 'mment donné il me semble
    }
    delete[] notes;

    for(unsigned int i = 0; i<nbRelations;i++){
        delete relations[i];
    }
    delete[] relations;
}

/**< TEMPLATE METHOD ITERATOR DANS LA CLASSE MANAGER POUR LES NOTES */

/**< Iterator de notes */

void Manager::IteratorNotes::next(){
    if(isDone()) throw NoteException("\nnext() sur un IteratorNotes fini !\n");
    remain--;
    currentN++;
}

Note& Manager::IteratorNotes::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un IteratorNotes fini !\n");
    return **currentN;
}

///**< Iterator de notes actives */

//Manager::IteratorNotesActive::IteratorNotesActive(Note** t, int n): currentN(t), remain(n){
//    while(remain>0 && (*currentN)->getEtat()!=active){
//        currentN++;
//        remain--;
//    }
//}

//void Manager::IteratorNotesActive::next(){
//    while(!isDone() && (*currentN)->getEtat()!=active){
//        remain--;
//        currentN++;
//    }
//}

//Note& Manager::IteratorNotesActive::current() const{
//    if(isDone()) throw NoteException("\ncurrent() sur un IteratorNotes fini !\n");
//    return **currentN;
//}

///**< Iterator de notes archivees */

//Manager::IteratorNotesArchivee::IteratorNotesArchivee(Note** t, int n): currentN(t), remain(n){
//    while(remain>0 && (*currentN)->getEtat()!=archivee){
//        currentN++;
//        remain--;
//    }
//}

//void Manager::IteratorNotesArchivee::next(){
//    while(!isDone() && (*currentN)->getEtat()!=archivee){
//        remain--;
//        currentN++;
//    }
//}

//Note& Manager::IteratorNotesArchivee::current() const{
//    if(isDone()) throw NoteException("\ncurrent() sur un IteratorNotes fini !\n");
//    return **currentN;
//}

///**< Iterator de notes dans l'etat corbeille */

//Manager::IteratorNotesCorbeille::IteratorNotesCorbeille(Note** t, int n): currentN(t), remain(n){
//    while(remain>0 && (*currentN)->getEtat()!=corbeille){
//        currentN++;
//        remain--;
//    }
//}

//void Manager::IteratorNotesCorbeille::next(){
//    while(!isDone() && (*currentN)->getEtat()!=corbeille){
//        remain--;
//        currentN++;
//    }
//}

//Note& Manager::IteratorNotesCorbeille::current() const{
//    if(isDone()) throw NoteException("\ncurrent() sur un IteratorNotes fini !\n");
//    return **currentN;
//}

/**< TEMPLATE METHOD ITERATOR DANS LA CLASSE MANAGER POUR LES RELATIONS */

void Manager::IteratorRelations::next(){
    if(isDone()) throw NoteException("\nnext() sur un IteratorRelation fini !\n");
    remain--;
    currentR++;
}

Relation& Manager::IteratorRelations::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un IteratorRelation fini !\n");
    return **currentR;
}

void Manager::ConstIteratorRelations::next(){
    if(isDone()) throw NoteException("\nnext() sur un ConstIteratorRelation fini !\n");
    remain--;
    currentR++;
}

const Relation& Manager::ConstIteratorRelations::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un ConstIteratorRelation fini !\n");
    return **currentR;
}

/**< METHODES DE CREATION DES DIFFERENTS NOTES */

unsigned long Manager::nextNoteID = 0;

void Manager::newArticle(const QString& ti, const QString& te){
    Article* a=new Article(nextNoteID++,ti,te);
    ajouterNote(*a);
}

void Manager::newTache(const QString& ti, const QString& act, int prio, const QDate& d){
    Tache* a=new Tache(nextNoteID++,ti,act,prio,d);
    ajouterNote(*a);
}

void Manager::newMultimedia(const QString& ti, const QString& adr, const QString& desc, TypeMultimedia ty){
    Multimedia* a=new Multimedia(nextNoteID++,ti,adr,ty,desc);
    ajouterNote(*a);
}

void Manager::ajouterNote(Note &n){
    if(nbNotes == nbNotesMax){
        Note** newtab = new Note* [Manager::nbNotesMax+5];
        for(unsigned int i=0;i<nbNotes;i++) newtab[i] = notes[i];
        Note** oldtab = notes;
        notes = newtab;
        nbNotesMax += 5;
        delete[] oldtab;
    }
    notes[nbNotes++] = &n;
    addRefsFromNote(n);
}

void Manager::addArticle(const int id, const QString& ti, const QDateTime& dc, const QDateTime& dm, bool act, NoteEtat e,const QString& te ){
    Article* a=new Article(id,ti,dc,dm,act,e,te);
    Manager::ajouterNote(*a);
}

void Manager::addTache(const int id, const QString& ti, const QDateTime& dc, const QDateTime& dm, bool act, NoteEtat e,const QString& acti, const int prio, const QDate& eche, const TacheStatut ts ){
    Tache* a=new Tache(id,ti,dc,dm,act,e,acti,prio,eche,ts);
    Manager::ajouterNote(*a);
}

void Manager::addMultimedia(const int id, const QString& ti, const QDateTime& dc, const QDateTime& dm, bool act, NoteEtat e,const QString& af, const TypeMultimedia ty,const QString& dec){
    Multimedia* a=new Multimedia(id,ti,dc,dm,act,e,af,ty,dec);
    Manager::ajouterNote(*a);
}

/**< Methode permettant de rechercher une note à partir d'un ID */

Note* Manager::getNoteID(unsigned long id){
    for(IteratorNotes it=getIteratorNotes(); !it.isDone();it.next())
        if (it.current().getID()==id && it.current().isActuelle())
            return &(it.current());
    return nullptr;
}

/**< Methode permettant de rechercher une relation à partir d'un titre */

Relation& Manager::getRelation(const QString& t){
    for(IteratorRelations it=getIteratorRelations();!it.isDone();it.next())
        if(it.current().getTitre() == t) return it.current();
    else throw NoteException("Aucune relation avec ce titre");
}

/**< METHODES D'AJOUT DE RELATIONS */

void Manager::addRelation(const QString& t, const QString& d, bool o){
    for(IteratorRelations it=getIteratorRelations();!it.isDone();it.next())
        if(it.current().getTitre() == t) throw NoteException("Une relation avec le meme titre existe deja !");

    if (nbRelations==nbRelationsMax){
        Relation** newtab= new Relation* [nbRelationsMax+5];
        for(unsigned int i=0; i<nbRelations;i++){
            newtab[i]=relations[i];
        }
        nbRelationsMax=nbRelationsMax+5;
        Relation** oldtab= relations;
        relations=newtab;
        delete[] oldtab;
    }
    relations[nbRelations++]= new Relation(t, d, o);
}

//Ajouter un couple à une relation

void Manager::addCoupleRelation(Relation& r, unsigned int id1, unsigned int id2, const QString& lab){
    r.addCouple(id1,id2,lab);
}

//Ajouter un couple à la relation reference

void Manager::addCoupleReference(unsigned int id1, unsigned int id2, const QString& lab){
    reference.addCouple(id1,id2,lab);
}

//AddRefsFromNote du Manager qui permet d'ajouter toute les references contenues dans tous les champs de texte d'une Note

void Manager::addRefsFromNote(const Note& n){
    n.addRefs();
}

bool Manager::isReferenced(const Note& n) const{
    Reference& r=Reference::donneInstance();
    for(Relation::IteratorCouples it=r.getIteratorCouples();!it.isDone();it.next())
        if(it.current().getID1()==n.getID() || it.current().getID2()==n.getID()) return true;
    return false;
}

/**< Methodes d'edition inutiles pour l'instant mais je prefere garder au cas ou */

Article& Manager::editTexteArticle(Article& A, const QString& s) {
    Article* a= new Article(A);
    a->setTexte(s);
    a->setActuelle();
    A.setAncienne();
    ajouterNote(*a);
    return *a;
}

Tache& Manager::editActionTache(Tache& T, const QString& s){
    Tache* t= new Tache(T);
    t->setAction(s);
    t->setActuelle();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
};

Tache& Manager::editStatutTache(Tache& T, TacheStatut s){
    Tache* t= new Tache(T);
    t->setStatut(s);
    t->setActuelle();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
};

Tache& Manager::editPrioriteTache(Tache& T, int p){
    Tache* t= new Tache(T);
    t->setPriorite(p);
    t->setActuelle();
    T.setAncienne();
    ajouterNote(*t);
    return *t;};

Tache& Manager::editEcheanceTache(Tache& T, const QDate& d){
    Tache* t= new Tache(T);
    t->setEcheance(d);
    t->setActuelle();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
};

Multimedia& Manager::editFichierMultimedia(Multimedia& M, const QString s){
    Multimedia* m= new Multimedia(M);
    m->setAdresseFichier(s);
    m->setActuelle();
    M.setAncienne();
    ajouterNote(*m);
    return *m;
};

//Suppression Archivage et Vidage de Corbeille

void Manager::supprimerNote(Note& n){
    if(isReferenced(n)){
        for(IteratorNotes it=getIteratorNotes();!it.isDone();it.next())
            if(it.current().getID()==n.getID())
                it.current().setEtat(archivee);
    }
    else
        for(IteratorNotes it=getIteratorNotes();!it.isDone();it.next())
            if(it.current().getID()==n.getID()) it.current().setEtat(corbeille);
}

void Manager::viderCorbeille(){
    unsigned int i=0;
    while (i<nbNotes){
        if(notes[i]->getEtat()==corbeille){
            Note* temp=notes[i];
            for(unsigned int j=i; j<nbNotes-1;j++)
                notes[j]=notes[j+1];
            delete temp;
            nbNotes--;
        }
        else i++;
    }
}

void Manager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NoteException("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    // qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement){
            // If it's named notes, we'll go to the next.
            if(xml.name() == "notes") continue;

            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "article") {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                QString texte;
                QString dateCrea;
                QString dateModif;
                QString actuel;
                QString etat;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }
                        if(xml.name() == "datecrea") {
                            xml.readNext(); dateCrea=xml.text().toString();
                            qDebug()<<"datecrea="<<dateCrea<<"\n";
                        }
                        if(xml.name() == "datemodif") {
                            xml.readNext(); dateModif=xml.text().toString();
                            qDebug()<<"datemodif="<<dateModif<<"\n";
                        }
                        if(xml.name() == "etat") {
                            xml.readNext(); etat=xml.text().toString();
                            qDebug()<<"etat="<<etat<<"\n";
                        }
                        if(xml.name() == "actuel") {
                            xml.readNext(); actuel=xml.text().toString();
                            qDebug()<<"actuel="<<actuel<<"\n";
                        }
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "texte") {
                            xml.readNext();
                            texte=xml.text().toString();
                            qDebug()<<"text="<<texte<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addArticle(identificateur.toInt(),titre,QDateTime::fromString(dateCrea,formatDateTime),QDateTime::fromString(dateModif,formatDateTime),Note::QStringtoActuel(actuel),Note::QStringtoNoteEtat(etat),texte );
            }

            if(xml.name() == "tache") {
                qDebug()<<"new tache\n";
                QString identificateur;
                QString titre;
                QString action;
                QString echeance;
                QString priorite;
                QString statut;
                QString dateCrea;
                QString dateModif;
                QString actuel;
                QString etat;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }
                        if(xml.name() == "datecrea") {
                            xml.readNext(); dateCrea=xml.text().toString();
                            qDebug()<<"datecrea="<<dateCrea<<"\n";
                        }
                        if(xml.name() == "datemodif") {
                            xml.readNext(); dateModif=xml.text().toString();
                            qDebug()<<"datemodif="<<dateModif<<"\n";
                        }
                        if(xml.name() == "etat") {
                            xml.readNext(); etat=xml.text().toString();
                            qDebug()<<"etat="<<etat<<"\n";
                        }
                        if(xml.name() == "actuel") {
                            xml.readNext(); actuel=xml.text().toString();
                            qDebug()<<"actuel="<<actuel<<"\n";
                        }
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "action") {
                            xml.readNext(); action=xml.text().toString();
                            qDebug()<<"action="<<action<<"\n";
                        }
                        if(xml.name() == "priorite") {
                            xml.readNext();
                            priorite=xml.text().toString();
                            qDebug()<<"priorite="<<priorite<<"\n";
                        }
                        if(xml.name() == "echeance") {
                            xml.readNext();
                            echeance=xml.text().toString();
                            qDebug()<<"echeance="<<echeance<<"\n";
                        }
                        if(xml.name() == "statut") {
                            xml.readNext();
                            statut=xml.text().toString();
                            qDebug()<<"statut="<<statut<<"\n";
                        }

                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addTache(identificateur.toInt(),titre,QDateTime::fromString(dateCrea,formatDateTime),QDateTime::fromString(dateModif,formatDateTime),Tache::QStringtoActuel(actuel),Tache::QStringtoNoteEtat(etat),action,priorite.toInt(),QDate::fromString(echeance,formatDate),Tache::QStringtoTacheStatut(statut));
            }

            if(xml.name() == "multimedia"){
                qDebug()<<"new multimedia\n";
                QString identificateur;
                QString titre;
                QString adressefichier;
                QString type;
                QString description;
                QString dateCrea;
                QString dateModif;
                //QString horaireCrea;
                //QString horaireModif;
                QString actuel;
                QString etat;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "multimedia")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }
                        if(xml.name() == "datecrea") {
                            xml.readNext(); dateCrea=xml.text().toString();
                            qDebug()<<"datecrea="<<dateCrea<<"\n";
                        }
                        // if(xml.name() == "horairecrea") {
                        //     xml.readNext(); horaireCrea=xml.text().toString();
                        //     qDebug()<<"horairecrea="<<horaireCrea<<"\n";
                        // }
                        if(xml.name() == "datemodif") {
                            xml.readNext(); dateModif=xml.text().toString();
                            qDebug()<<"datemodif="<<dateModif<<"\n";
                        }
                        // if(xml.name() == "horairemodif") {
                        //     xml.readNext(); horaireModif=xml.text().toString();
                        //     qDebug()<<"horairemodif="<<horaireModif<<"\n";
                        // }

                        if(xml.name() == "etat") {
                            xml.readNext(); etat=xml.text().toString();
                            qDebug()<<"etat="<<etat<<"\n";
                        }
                        if(xml.name() == "actuel") {
                            xml.readNext(); actuel=xml.text().toString();
                            qDebug()<<"actuel="<<actuel<<"\n";
                        }
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }

                        if(xml.name() == "adressefichier") {
                            xml.readNext(); adressefichier=xml.text().toString();
                            qDebug()<<"adressefichier="<<adressefichier<<"\n";
                        }

                        if(xml.name() == "type") {
                            xml.readNext();
                            type=xml.text().toString();
                            qDebug()<<"type="<<type<<"\n";
                        }
                        if(xml.name() == "description") {
                            xml.readNext();
                            description=xml.text().toString();
                            qDebug()<<"description="<<description<<"\n";
                        }

                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addMultimedia(identificateur.toInt(),titre,QDateTime::fromString(dateCrea,formatDateTime),QDateTime::fromString(dateModif,formatDateTime),Note::QStringtoActuel(actuel),Note::QStringtoNoteEtat(etat),adressefichier, Multimedia::QStringtoTypeMultimedia(type), description);
            }
        }
    }

    // Error handling.
    if(xml.hasError()) throw NoteException("Erreur lecteur fichier notes, parser xml");
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}

void Manager::save()const{
 QFile newfile(filename);
     if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NoteException(QString("erreur sauvegarde notes : ouverture fichier xml"));
        QXmlStreamWriter stream(&newfile);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("notes");
        for(unsigned int i=0; i<nbNotes; i++){
            notes[i]->saveNote(stream);
        }
        stream.writeEndElement();
        stream.writeEndDocument();
        newfile.close();
}
