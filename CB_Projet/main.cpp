#include "timing.h"
#include "PluriNotes.h"

using namespace TIME;

int main(int argc, const char * argv[])
{
    // insert code here... modification test

   Note n(3,"soucis");
   Note n2(n);

   n.afficher();
   n2.afficher();

   std::cout << "\nBranch Pierre\n";

    return 0;
}
