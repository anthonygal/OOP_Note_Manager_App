#include <iostream>
#include "timing.h"
#include<iostream>
#include<iomanip>
#include <ctime>
#include "PluriNotes.h"

using namespace std;
using namespace TIME;

int main(int argc, const char * argv[])
{
    // insert code here... modification test

   Date d;
   d.afficher();
   Horaire h;
   h.afficher ();

   Note n("soucis");
   cout<<n.getdateModif()<<" "<<n.getdateCrea()<<"\n"<<n.gethoraireCrea()<<" "<<n.gethoraireModif()<<" "<<n.getactuel()<<" "<<n.gettitre();


    return 0;
}
