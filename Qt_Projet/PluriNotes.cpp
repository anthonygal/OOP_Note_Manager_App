#include "PluriNotes.h"
#include <QFile>

using namespace TIME;

/**< CONSTRUCTEUR DE RECOPIE DE LA CLASS NOTE */

Note::Note(Note& n){
    ID = n.ID;
    titre = n.titre;
    dateCrea = n.dateCrea;
    horaireCrea = n.horaireCrea;
    dateModif = dateNow();
    horaireModif = horaireNow();
    etat = n.etat;
    actuel = true;
    n.setAncienne();
}

/**< METHODES D'AFFICHAGE DES DIFFERENTES NOTES */
/*
void Note::afficher(std::ostream& f) const {
    f<<"\n------ "<<typeid(*this).name()<<" "<<ID<<(actuel?" (Version Actuelle)":" (Ancienne Version)")<<" ------\n";
    f<<"\nID : "<<ID;
    f<<"\nTitre : "<<titre;
    f<<"\nCree le : "<<dateCrea<<" a "<<horaireCrea;
    f<<"\nModifie le "<<dateModif<<" a "<<horaireModif;
    f<<"\nEtat : ";
    switch(etat){
        case 0: f<<"Active"; break;
        case 1: f<<"Archivee"; break;
        case 2: f<<"Dans la corbeille"; break;
    }
    afficherSpecifique(f);
    f<<"\n\n-------\n";
}

void Article::afficherSpecifique(std::ostream& f) const {
    f<<"\nTexte : "<<texte;
}

void Tache::afficherSpecifique(std::ostream& f) const {
    f<<"\nAction : "<<action;
    f<<"\nStatut : ";
    switch(statut){
        case 0: f<<"Attente"; break;
        case 1: f<<"En cours"; break;
        case 2: f<<"Terminee"; break;}
    if (priorite!=0){
    f<<"\nPriorite : "<<priorite;
    }
    if (echeance.getAnnee()!=0 || echeance.getMois()!=1 || echeance.getJour()!=1  ){
    f<<"\nEcheance : "<<echeance;
    }
}

void Multimedia::afficherSpecifique(std::ostream& f) const {
    f<<"\nAdresseFichier : "<<adresseFichier;
    f<<"\nDescription : "<<description;
    f<<"\nType : ";
    switch(type){
        case 0: f<<"image"; break;
        case 1: f<<"video"; break;
        case 2: f<<"audio"; break;}
}
*/
/*
std::ostream& operator<<(std::ostream& f, const Note& n) {
        n.afficher(f);
        return f;
}*/

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

void Manager::IteratorNotes::next(){
    if(isDone()) throw NoteException("\nnext() sur un IteratorNotes fini !\n");
    remain--;
    currentN++;
}

Note& Manager::IteratorNotes::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un IteratorNotes fini !\n");
    return **currentN;
}

void Manager::ConstIteratorNotes::next(){
    if(isDone()) throw NoteException("\nnext() sur un ConstIteratorNotes fini !\n");
    remain--;
    currentN++;
}

const Note& Manager::ConstIteratorNotes::current() const{
    if(isDone()) throw NoteException("\ncurrent() sur un ConstIteratorNotes fini !\n");
    return **currentN;
}

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

void Manager::newTache(const QString& ti, const QString& act, int prio, Date d){
    Tache* a=new Tache(nextNoteID++,ti,act,prio,d);
    ajouterNote(*a);
}

void Manager::newMultimedia(const QString& ti, const QString& adr, const QString& desc, TypeMultimedia ty){
    Multimedia* a=new Multimedia(nextNoteID++,ti,adr,ty,desc);
    ajouterNote(*a);
}

void Manager::ajouterNote(Note& n){
    if(nbNotes == nbNotesMax){
        Note** newtab = new Note* [Manager::nbNotesMax+5];
        for(unsigned int i=0;i<nbNotes;i++) newtab[i] = notes[i];
        Note** oldtab = notes;
        notes = newtab;
        nbNotesMax += 5;
        delete[] oldtab;
    }
    notes[nbNotes++] = &n;
};

/**< DEMANDES D'EDITION DES DIFFERENTS NOTES */
/**< MODIFIER LES CIN/COUT LORS DE LA MISE EN PLACE DE QT */

/*
void Manager::editNote(Note& n){
    Note& n2=n.edit();
    ajouterNote(n2);
}


Article& Article::edit(){
    QString newTitle;
    QString newText;
    std::cout<<"\nAncien titre : "<<this->getTitre()<<"\tNouveau titre : ";
    std::cin>>newTitle;
    std::cout<<"\nAncien texte : "<<this->getTexte()<<"\tNouveau texte : ";
    std::cin>>newText;
    Article* a=new Article(*this);
    a->setTitre(newTitle);
    a->setTexte(newText);
    return *a;
}
*/


/*


Tache& Tache::edit(){
    QString newTitle;
    std::string newAction;
    int newPriorite;
    TIME::Date newEcheance;
    std::cout<<"\nAncien titre : "<<this->getTitre()<<"\tNouveau titre : ";
    std::cin>>newTitle;
    std::cout<<"\nAncienne action : "<<this->getAction()<<"\tNouvelle action : ";
    std::cin>>newAction;
    std::cout<<"\nAncienne priorite : "<<this->getPriorite()<<"\tNouvelle priorite : ";
    std::cin>>newPriorite;
    std::cout<<"\nAncienne date d'echeance : "<<this->getEcheance()<<"\tNouvelle date d'echeance : ";
    std::cin>>newEcheance;
    Tache* t=new Tache(*this);
    t->setTitre(newTitle);
    t->setAction(newAction);
    t->setPriorite(newPriorite);
    t->setEcheance(newEcheance);
    return *t;
}

Multimedia& Multimedia::edit(){
    QString newTitle;
    std::string newAdresseFichier;
    std::string newTypeString;
    TypeMultimedia newType;
    std::string newDescription;
    std::cout<<"\nAncien titre : "<<this->getTitre()<<"\tNouveau titre : ";
    std::cin>>newTitle;
    std::cout<<"\nAncienne adresse fichier : "<<this->getAdresseFichier()<<"\tNouvelle adresse fichier : ";
    std::cin>>newAdresseFichier;
    do{
        std::cout<<"\nAncienne type : "<<this->getType()<<"\tNouveau type (choisir entre image/video/audio) : ";
        std::cin>>newTypeString;
    }while(newTypeString!="image" && newTypeString!="video" && newTypeString!="audio");
    if(newTypeString=="image") newType=image;
    if(newTypeString=="video") newType=video;
    if(newTypeString=="audio") newType=audio;
    std::cout<<"\nAncienne description : "<<this->getDescription()<<"\tNouvelle description : ";
    std::cin>>newDescription;
    Multimedia* m=new Multimedia(*this);
    m->setTitre(newTitle);
    m->setAdresseFichier(newAdresseFichier);
    m->setType(newType);
    m->setDescription(newDescription);
    return *m;
*/

void Manager::save()const{
 QFile newfile(filename);
     if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NoteException(QString("erreur sauvegarde notes : ouverture fichier xml"));
        QXmlStreamWriter stream(&newfile);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("notes");
        for(int i=0; i<nbNotes; i++){
            notes[i]->saveNote(stream);
        }
        stream.writeEndElement();
        stream.writeEndDocument();
        newfile.close();
    }


void Article::saveNote(QXmlStreamWriter& stream)const{
    stream.writeStartElement("article");
    unsigned int n = getID();
     QString str = "";
     str = QString::number(n);
    stream.writeTextElement("id",str);
    stream.writeTextElement("datecrea",getDateCrea().DatetoQString());
    stream.writeTextElement("horairecrea",getHoraireCrea().HorairetoQString());
    stream.writeTextElement("datemodif",getDateModif().DatetoQString());
    stream.writeTextElement("horairemodif",getHoraireModif().HorairetoQString());
    stream.writeTextElement("etat",NoteEtattoQString());
    stream.writeTextElement("actuel",ActueltoQString());
    stream.writeTextElement("titre",getTitre());
    stream.writeTextElement("texte",getTexte());
    stream.writeEndElement();
}

void Tache::saveNote(QXmlStreamWriter& stream)const{
    stream.writeStartElement("tache");
    unsigned int n = getID();
     QString str = "";
     str = QString::number(n);
    stream.writeTextElement("id",str);
    stream.writeTextElement("datecrea",getDateCrea().DatetoQString());
    stream.writeTextElement("horairecrea",getHoraireCrea().HorairetoQString());
    stream.writeTextElement("datemodif",getDateModif().DatetoQString());
    stream.writeTextElement("horairemodif",getHoraireModif().HorairetoQString());
    stream.writeTextElement("etat",NoteEtattoQString());    
    stream.writeTextElement("actuel",ActueltoQString());
    stream.writeTextElement("titre",getTitre());
    stream.writeTextElement("action",getAction());
    QString str2 = "";
    str2 = QString::number(getPriorite());
    stream.writeTextElement("priorite",str2);
    stream.writeTextElement("echeance",getEcheance().DatetoQString());
    stream.writeTextElement("statut",TacheStatuttoQString());
    stream.writeEndElement();
}

void Multimedia::saveNote(QXmlStreamWriter& stream)const{
    stream.writeStartElement("tache");
    unsigned int n = getID();
     QString str = "";
     str = QString::number(n);
    stream.writeTextElement("id",str);
    stream.writeTextElement("datecrea",getDateCrea().DatetoQString());
    stream.writeTextElement("horairecrea",getHoraireCrea().HorairetoQString());
    stream.writeTextElement("datemodif",getDateModif().DatetoQString());
    stream.writeTextElement("horairemodif",getHoraireModif().HorairetoQString());
    stream.writeTextElement("etat",NoteEtattoQString()); 
    stream.writeTextElement("actuel",ActueltoQString());
    stream.writeTextElement("titre",getTitre());
    stream.writeTextElement("adressefichier",getAdresseFichier());
    stream.writeTextElement("type",TypeMultimediatoQString());
    stream.writeTextElement("description",getDescription());
    stream.writeEndElement();
}


QString Note::NoteEtattoQString()const{
    QString str="";
    if (etat==active){str="active";}
    if (etat==archivee){str="archivee";}
    if (etat==corbeille){str="corbeille";}
    return str;}


QString Tache::TacheStatuttoQString()const{
    QString str="";
    if (statut==attente){str="attente";}
    if (statut==encours){str="encours";}
    if (statut==terminee){str="terminee";}
    return str;}


QString Multimedia::TypeMultimediatoQString() const{
        QString str="";
        if (type==image){str="image";}
        if (type==video){str="video";}
        if (type==audio){str="audio";}
        return str;}

QString Note::ActueltoQString()const{
    QString str="";
    if (actuel==true){str='true';}
    else{str='false';}
    return str;
}



void Manager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NoteException("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;

            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "article") {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                QString texte;
                QString dateCrea;
                QString dateModif;
                QString horaireCrea;
                QString horaireModif;
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
                        if(xml.name() == "horairecrea") {
                            xml.readNext(); horaireCrea=xml.text().toString();
                            qDebug()<<"horairecrea="<<horaireCrea<<"\n";
                        }
                        if(xml.name() == "datemodif") {
                            xml.readNext(); dateModif=xml.text().toString();
                            qDebug()<<"datemodif="<<dateModif<<"\n";
                        }
                        if(xml.name() == "horairemodif") {
                            xml.readNext(); horaireModif=xml.text().toString();
                            qDebug()<<"horairemodif="<<horaireModif<<"\n";
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
                addArticle(identificateur.toInt(),titre,TIME::Date::QStringtoDate(dateCrea), TIME::Horaire::QStringtoHoraire(horaireCrea),
                           TIME::Date::QStringtoDate(dateModif),TIME::Horaire::QStringtoHoraire(horaireModif),Note::QStringtoActuel(actuel),Note::QStringtoNoteEtat(etat),texte );
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
                QString horaireCrea;
                QString horaireModif;
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
                        if(xml.name() == "horairecrea") {
                            xml.readNext(); horaireCrea=xml.text().toString();
                            qDebug()<<"horairecrea="<<horaireCrea<<"\n";
                        }
                        if(xml.name() == "datemodif") {
                            xml.readNext(); dateModif=xml.text().toString();
                            qDebug()<<"datemodif="<<dateModif<<"\n";
                        }
                        if(xml.name() == "horairemodif") {
                            xml.readNext(); horaireModif=xml.text().toString();
                            qDebug()<<"horairemodif="<<horaireModif<<"\n";
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
                addTache(identificateur.toInt(), titre,TIME::Date::QStringtoDate(dateCrea),TIME::Horaire::QStringtoHoraire(horaireCrea),TIME::Date::QStringtoDate(dateModif),TIME::Horaire::QStringtoHoraire(horaireModif),Tache::QStringtoActuel(actuel),Tache::QStringtoNoteEtat(etat),action,priorite.toInt(), TIME::Date::QStringtoDate(echeance), Tache::QStringtoTacheStatut(statut));

                }
            }
            if(xml.name() == "multimedia") {
                qDebug()<<"new multimedia\n";
                QString identificateur;
                QString titre;
                QString adressefichier;
                QString type;
                QString description;
                QString dateCrea;
                QString dateModif;
                QString horaireCrea;
                QString horaireModif;
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
                        if(xml.name() == "horairecrea") {
                            xml.readNext(); horaireCrea=xml.text().toString();
                            qDebug()<<"horairecrea="<<horaireCrea<<"\n";
                        }
                        if(xml.name() == "datemodif") {
                            xml.readNext(); dateModif=xml.text().toString();
                            qDebug()<<"datemodif="<<dateModif<<"\n";
                        }
                        if(xml.name() == "horairemodif") {
                            xml.readNext(); horaireModif=xml.text().toString();
                            qDebug()<<"horairemodif="<<horaireModif<<"\n";
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
                addMultimedia(identificateur.toInt(),titre,TIME::Date::QStringtoDate(dateCrea), TIME::Horaire::QStringtoHoraire(horaireCrea),
                           TIME::Date::QStringtoDate(dateModif),TIME::Horaire::QStringtoHoraire(horaireModif),Note::QStringtoActuel(actuel),Note::QStringtoNoteEtat(etat),adressefichier, Multimedia::QStringtoTypeMultimedia(type), description);
                }
            }


    // Error handling.
    if(xml.hasError()) {
        throw NoteException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}



void Manager::addArticle(const int id, const QString& ti, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e,const QString& te ){
    Article* a=new Article(id,ti,dc,hc,dm,hm,act,e,te);
    Manager::ajouterNote(*a);
}




void Manager::addTache(const int id, const QString& ti, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e,const QString& acti, const int prio, const Date eche, const TacheStatut ts ){
    Tache* a=new Tache(id,ti,dc,hc,dm,hm,act,e,acti, prio, eche, ts);
    Manager::ajouterNote(*a);
}



void Manager::addMultimedia(const int id, const QString& ti, const Date dc, const Horaire hc, const Date dm, const Horaire hm, bool act, NoteEtat e,const QString& af, const TypeMultimedia ty,const QString& dec){
    Multimedia* a=new Multimedia(id,ti,dc,hc,dm,hm,act,e,af,ty,dec);
    Manager::ajouterNote(*a);
}




NoteEtat Note::QStringtoNoteEtat(const QString& str){
    if (str=="active"){return active; }
    if (str=="archivee"){return archivee; }
    if (str=="corbeille"){return corbeille; }
}

TacheStatut Tache::QStringtoTacheStatut(const QString & str){
    if (str=="attente"){return attente;}
    if (str=="encours"){return encours;}
    if (str=="terminee"){return terminee;}
 }


TypeMultimedia Multimedia::QStringtoTypeMultimedia(const QString & str){
        if (str=="image"){return image;}
        if (str=="video"){return video;}
        if (str=="audio"){return audio;}
  }

bool Note::QStringtoActuel(const QString & str){
    if (str=='true'){return true;}
    else{return false;}
}


/**< METHODES D'AJOUT DE RELATIONS */



void Manager::addRelation(Relation& r){
    if (nbRelations==nbRelationsMax){
        Relation** newtab= new Relation* [nbRelationsMax+5];
        for(unsigned int i=0; i<nbRelations;i++){
            newtab[i]=relations[i];
        }
        nbRelationsMax=nbRelationsMax+5;
        Relation** oldtab= relations;
        relations=newtab;
        delete [] oldtab;
    }
    relations[nbRelations]=&r;
    nbRelations++;
}

void Manager::addCoupleRelation(Relation& r, Couple& c) {
    r.addCouple(c);
}


/**< TEMPLATE METHOD SINGLETON POUR LA CLASS REFERENCE */

Reference& Manager::getReference() {
    Reference& R=Reference::donneInstance();
    return R;
}

/**< Methode permettant de rechercher une note à partir d'un ID */
Note* Manager::searchID(unsigned long id){
    for (unsigned int i=0; i<nbNotes;i++){
        if (notes[i]->getID()==id){
            if (notes[i]->getActuel()) {
                return notes[i];
            }
        }
    }
    return nullptr;
}

/**< Methodes d'edition inutiles pour l'instant mais je prefere garder au cas ou */

Article& Manager::editTexteArticle(Article& A, const QString& s) {
    Article* a= new Article(A);
    a->setTexte(s);
    a->setActuel();
    A.setAncienne();
    ajouterNote(*a);
    return *a;
}

Tache& Manager::editActionTache(Tache& T, const QString& s){
    Tache* t= new Tache(T);
    t->setAction(s);
    t->setActuel();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
};

Tache& Manager::editStatutTache(Tache& T, TacheStatut s){
    Tache* t= new Tache(T);
    t->setStatut(s);
    t->setActuel();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
};

Tache& Manager::editPrioriteTache(Tache& T, int p){
    Tache* t= new Tache(T);
    t->setPriorite(p);
    t->setActuel();
    T.setAncienne();
    ajouterNote(*t);
    return *t;};

Tache& Manager::editEcheanceTache(Tache& T, TIME::Date d){
    Tache* t= new Tache(T);
    t->setEcheance(d);
    t->setActuel();
    T.setAncienne();
    ajouterNote(*t);
    return *t;
};

Multimedia& Manager::editFichierMultimedia(Multimedia& M, const QString s){
    Multimedia* m= new Multimedia(M);
    m->setAdresseFichier(s);
    m->setActuel();
    M.setAncienne();
    ajouterNote(*m);
    return *m;
};

//Ajouter un couple à la relation reference


void Manager::addCoupleReference(Couple& c){
    Reference& R=this->getReference();
    R.addCouple(c);
}

// Ajout de toutes les references contenues dans les champs de texte d'une notes avec Template Method

void Note::AddRefs(Manager& m){
    unsigned long ID=findRefID(this->getTitre(), 0);
    int pos=0;
    while (ID!=-1){
        Note* N=m.searchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            m.addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getTitre(), pos);
    }
    AddRefsSpecifique(m);
}


//AddrefsSpeacifique(Manager& m) Specifique a chaque sous class de Note


void Tache::AddRefsSpecifique(Manager& m){
    unsigned long ID=findRefID(this->getAction(), 0);
    int pos=0;
    while (ID!=-1){
        Note* N=m.searchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            m.addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getAction(), pos);
        ID=findRefID(this->getAction(), pos);
    }
}

void Article::AddRefsSpecifique(Manager& m){
    unsigned long ID=findRefID(this->getTexte(), 0);
    int pos=0;
    while (ID!=-1){
        Note* N=m.searchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            m.addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getTexte(), pos);
        ID=findRefID(this->getTexte(), pos);
    }
}

void Multimedia::AddRefsSpecifique(Manager& m){
    unsigned long ID=findRefID(this->getDescription(), 0);
    int pos=0;
    while (ID!=-1){
        Note* N=m.searchID(ID);
        if (N!=nullptr) {
            Couple* C=new Couple(this,N,"");
            m.addCoupleReference(*C);
        }
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getDescription(), pos);
        ID=findRefID(this->getDescription(), pos);
    }
}


//AddRefsFromNote du Manager qui permet d'ajouter toute les references contenues dans tous les champs de texte d'une Note

void Manager::AddRefsFromNote(Note& N){
    N.AddRefs(*this);
}

bool Manager::isReferenced(const Note& N) const{
    Reference& R=Reference::donneInstance();
    if (R.getnbCouples()==0) return false;
    Couple* c=*(R.getCouples());
    Note* a;
    Note* b;
    int i=0;
    while (i<R.getnbCouples()) {
        a=c->getNote1();
        b=c->getNote2();
        if ((a->getID()==N.getID() && a->getActuel()) || (b->getID()==N.getID() && b->getActuel())) return true;
        i++;
    }
    return false;
}

//Suppression Archivage et Vidage de Corbeille

void Manager::supprimer(Note& N){
    if (isReferenced(N)) {
        N.setEtat(archivee);
        N.setAncienne();
        int i=0;
        while (i<nbNotes){
            if (notes[i]->getID()==N.getID()){
                notes[i]->setAncienne();
                notes[i]->setEtat(archivee);
            }
            i++;
        }
    }
    else {
        
        N.setEtat(corbeille);
        int i=0;
        while (i<nbNotes){
            if (notes[i]->getID()==N.getID()){
                notes[i]->setAncienne();
                notes[i]->setEtat(corbeille);
            }
            i++;
        }
    }
}

void Manager::viderCorbeille(){
    int i=0;
    while (i<nbNotes){
        if (notes[i]->getEtat()==corbeille){
            Note* temp=notes[i];
            for (int j=i; j<nbNotes-1; j++){
                notes[j]=notes[j+1];
            }
            delete temp;
            nbNotes--;
        }
        i++;
    }
}
