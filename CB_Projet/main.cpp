#include "timing.h"
#include "PluriNotes.h"

using namespace TIME;

int main()
{
    // insert code here... modification test
    Article* a = new Article(4,"test","try");
    std::cout<<*a;
    delete a;

    Manager& m=Manager::donneInstance();
    m.newTache("soucis","action",1,Date(03,06,2017));
    m.newArticle("souciss","pluie");
    for(Manager::IteratorNotes it=m.getIteratorNotes();!it.isDone();it.next()){
      if(it.current().getTitre()=="souciss") m.editNote(it.current());
    }
    for(Manager::ConstIteratorNotes it=m.getConstIteratorNotes();!it.isDone();it.next()){
      std::cout<<it.current();
    }
    m.libereInstance();


//
//    Manager& m=Manager::donneInstance();
//
//
//    Article& a=m.NewArticle(3,"soucis","yooo");
//    Article& a2=m.NewArticle(5,"soucis2","trop de problemes ref{3}hjh");
//    Article& a3=m.NewArticle(6,"soucis3","trop de problemes");
//    Article& a4=m.NewArticle(12,"soucis4","trop de problemes");
//    Article& a5=m.NewArticle(8,"soucis5","trop de problemes");
//
//    Tache& t=m.NewTache(7, "Commit vite!", "Il faut commit des choses intelligentes");
//    t.afficher();
//    //std::cout << a;
//    //std::cout << a2;std::cout << a3;std::cout << a4;std::cout << a5;
//    a2.afficher();
//
//
//    Multimedia& multimed=m.NewMultimedia(1,"unmultimedia","C:/fausseAdresse/test/velo.jpg", "description dun velo ref{3}h", image);
//
//
//
//    m.editTexteArticle(a5, "Edtion texte a6");
//
//    m.editFichierMultimedia(multimed, "Desktop/etc/kabul.jpg");
//
//     std::cout<<m.getnbNotes();
//
//    //m.Affichertout();
//
//    if (multimed.getActuel()==true) {std::cout<< "multimed actuel=true \n\n";} else {std::cout<<"multimed actuel=false  \n\n";};
//
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

    return 0;
}
