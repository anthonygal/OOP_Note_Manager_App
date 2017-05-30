#include "timing.h"
#include "PluriNotes.h"
#include "Relations.h"

using namespace TIME;

int main()
{
    // insert code here... modification test
    
    Manager& m=Manager::donneInstance();
    
    
    Article& a=m.NewArticle(3,"soucis");
    Article& a2=m.NewArticle(5,"soucis2","trop de problemes\ref{3}hjh");
    Article& a3=m.NewArticle(6,"soucis3","trop de problemes");
    Article& a4=m.NewArticle(7,"soucis4","trop de problemes");
    Article& a5=m.NewArticle(8,"soucis5","trop de problemes");
    
    Tache& t=m.NewTache(7, "Commit vite!", "Il faut commit des choses intelligentes");
    t.afficher();
    //std::cout << a;
    //std::cout << a2;std::cout << a3;std::cout << a4;std::cout << a5;
    a2.afficher();
    
    
    Multimedia& multimed=m.NewMultimedia(1,"unmultimedia","C:/fausseAdresse/test/velo.jpg", "description dun velo", image);

 
    
    m.editTexteArticle(a5, "Edtion texte a6");
    
    m.editFichierMultimedia(multimed, "Desktop/etc/kabul.jpg");
    
     std::cout<<m.getnbNotes();

   //m.Affichertout();
    
    if (multimed.getActuel()==true) {std::cout<< "multimed actuel=true \n\n";} else {std::cout<<"multimed actuel=false  \n\n";};
    
    
    Couple c= Couple::Couple(&a2, &a3, "lelabel");
    Relation* r= new Relation::Relation("tesrel","tedescri",true);
    m.addRelation(*r);
    m.addCoupleRelation(*r, c);
    //m.addCoupleReference(c);
    
    Reference& R=m.getReference();
    Reference& R2=m.getReference();
    
    
    std::cout<<m.getnbNotes()<<"\n";
    std::cout<<m.getnbRelations()<<"\n";
    
    
    

    //std::cout<<"\ntype de a : "<<typeid(a).name()<<"\n"; //Ca affiche un chiffre devant la classe mais je n'arrive pas à l'enlever...

    return 0;
}
