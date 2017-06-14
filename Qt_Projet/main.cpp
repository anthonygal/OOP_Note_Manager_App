#include "timing.h"
#include "Notes.h"
#include "FenetrePrincipale.h"
#include <QFile>
#include <QFileDialog>
#include <QApplication>

using namespace TIME;

int main(int argc, char* argv[])
{
    // insert code here... modification test
//
//    Couple* c= new Couple(&a2, &a3, "lelabel");
//    Relation* r= new Relation("tesrel","tedescri",true);
//    m.addRelation(*r);
//    m.addCoupleRelation(*r, *c);
//    //m.addCoupleReference(c);
//
//    Reference& R=m.getReference();
//    std::cout<<findRefID(a2.getTexte(), 0)<<"\n";
//
//    Note* n=m.SearchID(3);
//    std::cout<<n->getTitre()<<" : titre \n";
//
//
//    std::cout<<m.getnbNotes()<<": nbNotes \n";
//
//    //m.AddRefsFromNote(a2);
//
//    std::cout<<m.getnbRelations()<<"nb Relations \n";
//    Couple* coum=new Couple(&multimed, &a2, "");
//    m.addCoupleReference(*coum);
//    m.AddRefsFromNote(multimed);
//    std::cout<<findRefID(multimed.getDescription(),0)<<"\n";
//    std::cout<<getPosition(multimed.getDescription(),0)<<"\n";
//    std::cout<<multimed.getDescription()<<"\n";
//    std::cout<<R.getnbCouples()<<"\n";
//
//
//
//    //std::cout<<"\ntype de a : "<<typeid(a).name()<<"\n"; //Ca affiche un chiffre devant la classe mais je n'arrive pas � l'enlever...

    QApplication app(argc, argv);

    Manager& m=Manager::donneInstance();
    //QString fichier = QFileDialog::getOpenFileName();
    //m.setFilename(fichier);
    m.setFilename("notes2.xml");
    m.load();

    FenetrePrincipale fenetre;
    fenetre.show();

    return app.exec();
}
