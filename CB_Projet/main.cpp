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

   n.afficher();

   std::cout << "\nBranch Pierre\n";

    return 0;
}
