#include "timing.h"
#include "PluriNotes.h"
#include "Relations.h"

using namespace TIME;

int main()
{
    // insert code here... modification test

    Article a(3,"soucis");
   Article a2(5,"soucis2","trop de problemes");
    Article a3(6,"soucis3","trop de problemes");
    Article a4(7,"soucis4","trop de problemes");
    Article a5(8,"soucis5","trop de problemes");
    Article a6(9,"soucis6","trop de problemes");
   // std::cout<<"caca";
    Tache t(7, "Commit vite!", "Il faut commit des choses intelligentes");
    Date d (1,12,2017);
    Tache t2(8, "Test", "je vais craquer", 1, d);
    t2.afficher();
    //std::cout << a;
    //std::cout << a2;std::cout << a3;std::cout << a4;std::cout << a5;
    a.afficher();
   Manager m;
    
    Multimedia multimed(1,"unmultimedia","C:/fausseAdresse/test/velo.jpg", "description dun velo", image);

   m<<a<<a2<<a3<<a4<<a5<<a6<<t<<t2<<multimed;
    
    m.editTexteArticle(a6, "Edtion texte a6");
    
    m.editFichierMultimedia(multimed, "Desktop/etc/kabul.jpg");
    
     std::cout<<m.getnbNotes();

   m.Affichertout();
    
    if (multimed.getActuel()==true) {std::cout<< "multimed actuel=true \n\n";} else {std::cout<<"multimed actuel=false  \n\n";};
    


    //std::cout<<"\ntype de a : "<<typeid(a).name()<<"\n"; //Ca affiche un chiffre devant la classe mais je n'arrive pas à l'enlever...

    return 0;
}
