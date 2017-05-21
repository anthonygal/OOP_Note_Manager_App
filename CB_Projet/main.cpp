#include "timing.h"
#include "PluriNotes.h"

using namespace TIME;

int main(int argc, const char * argv[])
{
    // insert code here... modification test



   Note n("soucis");
   std::cout<<n.getdateModif()<<" "<<n.getdateCrea()<<"\n"<<n.gethoraireCrea()<<" "<<n.gethoraireModif()<<" "<<n.getactuel()<<" "<<n.gettitre();

    Note n2 (n);
   std::cout<<n2.getdateModif()<<" "<<n2.getdateCrea()<<"\n"<<n2.gethoraireCrea()<<" "<<n2.gethoraireModif()<<" "<<n2.getactuel()<<" "<<n2.gettitre();
    return 0;
}
