#include "Manager.h"
#include "FenetrePrincipale.h"

/*
void Manager::afficherTout()const{
    for(ConstIteratorNotes it=getConstIteratorNotes();!it.isDone();it.next()) std::cout<<it.current()<<std::endl;
}
*/

/**< TEMPLATE METHOD SINGLETON POUR LA CLASS MANAGER */

Manager* Manager::instanceUnique=nullptr;

Manager& Manager::donneInstance(){
    if (instanceUnique==nullptr) instanceUnique = new Manager;
    return *instanceUnique;
}

void Manager::libereInstance(){
    if (instanceUnique!=nullptr)
        delete instanceUnique;
    instanceUnique=nullptr;
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

/**< Methode permettant de rechercher une note à partir d'un ID */

Note* Manager::getNoteID(unsigned long id){
    for(IteratorNotes it=getIteratorNotes(); !it.isDone();it.next())
        if (it.current().getID()==id && it.current().isActuelle())
            return &(it.current());
    return nullptr;
}

/**< Methode permettant de rechercher une relation à partir d'un titre */

Relation& Manager::getRelation(const QString& t){
    for(IteratorRelations it=getIteratorRelations();!it.isDone();it.next()){
        if(it.current().getTitre() == t) return it.current();
    }
    throw NoteException("Aucune relation avec ce titre");
}

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

/**< Iterator de relations */

void Manager::IteratorRelations::next(){
    if(isDone()) throw NoteException("\nnext() sur un IteratorRelation fini !\n");
    remain--;
    currentR++;
}

Relation& Manager::IteratorRelations::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un IteratorRelation fini !\n");
    return **currentR;
}

/**< ConstIterator de relations */

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

//On recherche tous les couples de reference dont l'id de la note passées en argument correspond a l'id1 du couple et on supprimes ces couples.
//Ensuite comme on a supprimer des couples de reference on parcourt les notes archivees et si elles ne sont plus referencées, on les met dans la corbeille.
void Manager::suppRefsFromNote(const Note &n){
    for(Relation::IteratorCouples itc=reference.getIteratorCouples();!itc.isDone();itc.next())
        if(itc.current().getID1()==n.getID())
            reference.supprimerCouple(itc.current());
    for(IteratorNotes itn=getIteratorNotes();!itn.isDone();itn.next())
        if(itn.current().getEtat() == archivee && !isReferenced(itn.current()))
            itn.current().setEtat(corbeille);
}

//On parcourt tous les couples de reference et si l'ID de la note passée en argument correspond à l'ID2 d'un couple on renvoie vraie sinon faux.
bool Manager::isReferenced(const Note& n) const{
    for(Relation::IteratorCouples it=reference.getIteratorCouples();!it.isDone();it.next())
        if(it.current().getID2()==n.getID()) return true;
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
    return *t;}

Tache& Manager::editEcheanceTache(Tache& T, const QDate& d){
    Tache* t= new Tache(T);
    t->setEcheance(d);
    t->setActuelle();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
}

Multimedia& Manager::editFichierMultimedia(Multimedia& M, const QString s){
    Multimedia* m= new Multimedia(M);
    m->setAdresseFichier(s);
    m->setActuelle();
    M.setAncienne();
    ajouterNote(*m);
    return *m;
}

QString Manager::booltoQString(bool o){
    QString str="";
    if(o==true) str="true";
    else str="false";
    return str;
}

bool Manager::QStringtobool(const QString& str){
    if (str=="true") return true;
    else return false;
}

//Suppression Archivage et Vidage de Corbeille

void Manager::supprimerNote(Note& n){
    if(isReferenced(n)){
        for(IteratorNotes it=getIteratorNotes();!it.isDone();it.next())
            if(it.current().getID()==n.getID())
                it.current().setEtat(archivee);
    }
    else{
        suppRefsFromNote(n);
        for(IteratorNotes it=getIteratorNotes();!it.isDone();it.next())
            if(it.current().getID()==n.getID()) it.current().setEtat(corbeille);
    }
}

void Manager::viderCorbeille(){ // detruit les notes a la corbeille et couples associes
    unsigned int i=0;
    while (i<nbNotes){
        if(notes[i]->getEtat()==corbeille){
            Note* temp=notes[i];
            for(unsigned int j=i; j<nbNotes-1;j++)
                notes[j]=notes[j+1]; //La note est sortie du tableau
            for (IteratorRelations itr=getIteratorRelations();!itr.isDone();itr.next())   //On recherche les couples dans toutes les relation pour lesquelles la note est engagee.
                for(Relation::IteratorCouples itc=itr.current().getIteratorCouples();!itc.isDone();itc.next())
                    if(itc.current().getID1()==temp->getID() || itc.current().getID2()==temp->getID()) itr.current().supprimerCouple(itc.current());
            delete temp;
            nbNotes--;
        }
        else i++;
    }
}

void Manager::restaurerCorbeille(){
    for(IteratorNotes it=getIteratorNotes();!it.isDone();it.next())
        if(it.current().getEtat() == corbeille)
            it.current().setEtat(active);
}

void Manager::restaurerVersion(Note& n){
    for(IteratorNotes it=getIteratorNotes();!it.isDone();it.next())
        if(it.current().getID() == n.getID() && it.current().isActuelle())
            it.current().setAncienne();
    n.setActuelle();
}

void Manager::restaurerNote(Note& n){
    for(IteratorNotes it=getIteratorNotes();!it.isDone();it.next())
        if(it.current().getID() == n.getID())
            it.current().setEtat(active);
}

void Manager::load() {
    try{
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
            if(xml.name() == "manager") continue;

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

            if(xml.name() == "relation") {
                qDebug()<<"new relation\n";
                QString titre;
                QString description;
                QString orientee;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "relation")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "description") {
                            xml.readNext(); description=xml.text().toString();
                            qDebug()<<"description="<<description<<"\n";
                        }
                        if(xml.name() == "orientee") {
                            xml.readNext(); orientee=xml.text().toString();
                            qDebug()<<"orientee="<<orientee<<"\n";
                            addRelation(titre, description, QStringtobool(orientee));
                            qDebug()<<"creation relation "<<titre<<"\n";
                        }   
                        if(xml.name() == "couple") {
                            qDebug()<<"new couple\n";   
                            QString label;
                            QString ID1;
                            QString ID2;
                            QXmlStreamAttributes attributes = xml.attributes();
                            xml.readNext();
                            //We're going to loop over the things because the order might change.
                            //We'll continue the loop until we hit an EndElement named article.
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couple")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if(xml.name() == "label") {
                                         xml.readNext(); label=xml.text().toString();
                                         qDebug()<<"label="<<label<<"\n";
                                    }
                                    if(xml.name() == "ID1") {
                                        xml.readNext(); ID1=xml.text().toString();
                                        qDebug()<<"ID1="<<ID1<<"\n";
                                    }
                                    if(xml.name() == "ID2") {
                                        xml.readNext(); ID2=xml.text().toString();
                                        qDebug()<<"ID2="<<ID2<<"\n";
                                    }
                                }
                                xml.readNext();
                            }
                            addCoupleRelation(getRelation(titre), ID1.toInt(), ID2.toInt(), label);
                            qDebug()<<"ajout couple "<<label<<"\n";
                        }
                    }                       
                    xml.readNext();
                }
                qDebug()<<"fin ajout relation "<<titre<<"\n";
            }
//            if(xml.name() == "references") {
//                qDebug()<<"new relation\n";
//                QString titre;
//                QString description;
//                QString orientee;
//                QXmlStreamAttributes attributes = xml.attributes();
//                xml.readNext();
//                //We're going to loop over the things because the order might change.
//                //We'll continue the loop until we hit an EndElement named article.
//                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "relation")) {
//                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

//                        if(xml.name() == "couples") {
//                            qDebug()<<"new couple\n";
//                            QString label;
//                            QString ID1;
//                            QString ID2;
//                            QXmlStreamAttributes attributes = xml.attributes();
//                            xml.readNext();
//                            //We're going to loop over the things because the order might change.
//                            //We'll continue the loop until we hit an EndElement named article.
//                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couples")) {
//                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
//                                if(xml.name() == "label") {
//                                     xml.readNext(); label=xml.text().toString();
//                                     qDebug()<<"label="<<label<<"\n";
//                                    }
//                                 if(xml.name() == "ID1") {
//                                    xml.readNext(); ID1=xml.text().toString();
//                                    qDebug()<<"ID1="<<ID1<<"\n";
//                                    }
//                                if(xml.name() == "ID2") {
//                                    xml.readNext(); ID2=xml.text().toString();
//                                    qDebug()<<"ID2="<<ID2<<"\n";
//                                    }
//                                }
//                            xml.readNext();
//                            }
//                        qDebug()<<"ajout couple "<<label<<"\n";
//                        }
//                    }
//                    xml.readNext();
//                    addCoupleRelation(getRelation(titre), ID1.toInt(), ID2.toInt(), label);
//                }
//                qDebug()<<"ajout references "<<titre<<"\n";
//            }
        }
    }

    // Error handling.
    if(xml.hasError()) throw NoteException("Erreur lecteur fichier notes, parser xml");
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
    }catch(NoteException e){qDebug()<<e.getInfo()<<"\n";}
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
        for (unsigned int i=0; i<nbRelations;i++){
            relations[i]->saveRelation(stream);
        }
        stream.writeTextElement("NextNoteID",QString::number(nextNoteID));
        //reference.saveReference(stream);
        stream.writeEndElement();
        stream.writeEndDocument();
        newfile.close();
}

