#include "Notes.h"
#include "Manager.h"
#include "NoteEditeur.h"

/**< CONSTRUCTEUR DE RECOPIE DE LA CLASS NOTE */

Note::Note(Note& n){
    ID = n.ID;
    titre = n.titre;
    dateCrea = n.dateCrea;
    dateModif = QDateTime::currentDateTime();
    etat = n.etat;
    actuelle = true;
    n.setAncienne();
}

/**< DEMANDES D'EDITION DES DIFFERENTS NOTES */

void Article::edit(){
    ArticleEditeur *editeur = new ArticleEditeur(*this);
    editeur->show();
}

void Tache::edit(){
    TacheEditeur *editeur = new TacheEditeur(*this);
    editeur->show();
}

void Multimedia::edit(){
    MultimediaEditeur *editeur = new MultimediaEditeur(*this);
    editeur->show();
}

//changer la boucle for

void Article::saveNote(QXmlStreamWriter& stream)const{
    stream.writeStartElement("article");
    stream.writeTextElement("id",QString::number(getID()));
    stream.writeTextElement("datecrea",getDateCrea().toString(formatDateTime));
    stream.writeTextElement("datemodif",getDateModif().toString(formatDateTime));
    stream.writeTextElement("etat",NoteEtattoQString());
    stream.writeTextElement("actuel",ActueltoQString());
    stream.writeTextElement("titre",getTitre());
    stream.writeTextElement("texte",getTexte());
    stream.writeEndElement();
}

void Tache::saveNote(QXmlStreamWriter& stream)const{
    stream.writeStartElement("tache");
    stream.writeTextElement("id",QString::number(getID()));
    stream.writeTextElement("datecrea",getDateCrea().toString(formatDateTime));
    stream.writeTextElement("datemodif",getDateModif().toString(formatDateTime));
    stream.writeTextElement("etat",NoteEtattoQString());
    stream.writeTextElement("actuel",ActueltoQString());
    stream.writeTextElement("titre",getTitre());
    stream.writeTextElement("action",getAction());
    stream.writeTextElement("priorite",QString::number(getPriorite()));
    stream.writeTextElement("echeance",getEcheance().toString(formatDate));
    stream.writeTextElement("statut",TacheStatuttoQString());
    stream.writeEndElement();
}

void Multimedia::saveNote(QXmlStreamWriter& stream)const{
    stream.writeStartElement("multimedia");
    stream.writeTextElement("id",QString::number(getID()));
    stream.writeTextElement("datecrea",getDateCrea().toString(formatDateTime));
    stream.writeTextElement("datemodif",getDateModif().toString(formatDateTime));
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
    return str;
}


QString Tache::TacheStatuttoQString()const{
    QString str="";
    if (statut==attente){str="attente";}
    if (statut==encours){str="encours";}
    if (statut==terminee){str="terminee";}
    return str;
}


QString Multimedia::TypeMultimediatoQString() const{
        QString str="";
        if (type==image){str="image";}
        if (type==video){str="video";}
        if (type==audio){str="audio";}
        return str;
}

QString Note::ActueltoQString()const{
    QString str="";
    if (actuelle==true){str="Actuelle";}
    else{str="Ancienne";}
    return str;
}

NoteEtat Note::QStringtoNoteEtat(const QString& str){
    if (str=="active") return active;
    else if (str=="archivee") return archivee;
    else return corbeille;
}

TacheStatut Tache::QStringtoTacheStatut(const QString & str){
    if (str=="attente") return attente;
    else if (str=="terminee") return terminee;
    else return encours;

 }

TypeMultimedia Multimedia::QStringtoTypeMultimedia(const QString & str){
    if (str=="video") return video;
    if (str=="audio") return audio;
    else return image;
  }

bool Note::QStringtoActuel(const QString & str){
    if (str=="true") return true;
    else return false;
}

// Ajout de toutes les references contenues dans les champs de texte d'une notes avec Template Method

void Note::addRefs() const {
    Manager& m = Manager::donneInstance();
    long ID=findRefID(this->getTitre(), 0);
    int pos=0;
   while(ID!=-1){
     Note* n=m.getNoteID(ID);
     if (n!=nullptr) m.addCoupleReference(this->getID(),n->getID(),"ref");
     else throw NoteException("reference à une ID qui ne correspond à aucune Note");
     pos=getPosition(this->getTitre(), pos);
     ID=findRefID(this->getTitre(), pos);

    }
    addRefsSpecifique();
}

//AddrefsSpeacifique(Manager& m) Specifique a chaque sous class de Note

void Tache::addRefsSpecifique() const {
    Manager& m = Manager::donneInstance();
    long ID=findRefID(this->getAction(), 0);
    int pos=0;
    while (ID!=-1){
        Note* n=m.getNoteID(ID);
        if (n!=nullptr) m.addCoupleReference(this->getID(),n->getID(),"ref");
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getAction(), pos);
        ID=findRefID(this->getAction(), pos);
    }
}

void Article::addRefsSpecifique() const {
    Manager& m = Manager::donneInstance();
    long ID=findRefID(this->getTexte(), 0);
    int pos=0;
    while (ID!=-1){
        Note* n=m.getNoteID(ID);
        if (n!=nullptr) m.addCoupleReference(this->getID(),n->getID(),"ref");
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getTexte(), pos);
        ID=findRefID(this->getTexte(), pos);
    }
}

void Multimedia::addRefsSpecifique() const {
    Manager& m = Manager::donneInstance();
    long ID=findRefID(this->getDescription(), 0);
    int pos=0;
    while (ID!=-1){
        Note* n=m.getNoteID(ID);
        if (n!=nullptr) m.addCoupleReference(this->getID(),n->getID(),"ref");
        else throw NoteException("l'ID ne correspond a aucune Note");
        pos+=getPosition(this->getDescription(), pos);
        ID=findRefID(this->getDescription(), pos);
    }
}

// Fonction qui trouve dans tout string en partant de la position p si il y a une reference, dans ce cas, renvoie son ID, sinon, renvoie 0

long findRefID(const QString& s, int p){
    int l=s.length();
    QStringRef r=QStringRef(&s,p,l-p);
    int i=r.indexOf("\ref{");
    if (i!=-1) i+=4;
    int j=i;
    if (i!=-1){
        QChar c;
        c=r.at(i);
        if (!c.isDigit()) return -1;
        int idlength=0;
        while (c!='}' ) {
            idlength++;

            if (!c.isDigit()) return -1;
            i++;
            c=r.at(i);
        }
        //if(i==l-p) return -1;
        //else{
            QString f=r.toString();
            QStringRef x=QStringRef(&f,j,idlength);
            int id=x.toInt();
            return id;
        //}
    }
    else return -1;
}



//Fonction qui renvoie la position du "}" fermant la reference à partir de la position p passé en argument si une reference existe dans le string s, sinon renvoie 0

int getPosition(const QString& s, int p){
    int l=s.length();
    QStringRef r=QStringRef(&s,p,l-p);
    int i=r.indexOf("\ref{");
    if(i!=-1)i+=5;
    int j=i;
    if (i!=-1){
        QChar c=r.at(i);
        if (!c.isDigit()) return -1;
        int idlength=0;
        while (c!='}' && i<l-p){
            idlength++;
            if (!c.isDigit()) return -1;
            i++;
            c=r.at(i);
        }
        //if(i==l-p) return -1;
        return p+j+idlength;
    }
    else return -1;
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
