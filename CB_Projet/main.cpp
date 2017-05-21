#include "timing.h"
#include "PluriNotes.h"

using namespace TIME;

int main(int argc, const char * argv[])
{
    // insert code here... modification test

   Date d(dateNow());
   d.afficher();
   Horaire h(horaireNow());
   h.afficher();

   Note n("soucis");
   std::cout<<n.getdateModif()<<" "<<n.getdateCrea()<<"\n"<<n.gethoraireCrea()<<" "<<n.gethoraireModif()<<" "<<n.getactuel()<<" "<<n.gettitre();


    return 0;
}
