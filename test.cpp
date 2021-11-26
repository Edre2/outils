#include <iostream>
#include "outils.cpp"
using namespace std;

int main()
{
   
   string text = "";
   getline(cin, text);

   /* 
   Test des fonctions de formattage du text :
   cout << supprimerAccents(text) << "\n";
   cout << jolitexte(text) << "\n";
   cout << metttreMaj(text) << "\n";
   */
   
   cout << "\n\n";

   /*
   Test du codage vigenère :
   string mot = "";
   cin >> mot;
   cout << codagev(text, mot) << "\n";
   cout << jolitexte(decodagev(text, mot)) << "\n" ;
   */

   /*
   test de l'analyse de text :
   cout << analyse(text) << "\n";
   vector<int> alphabet;
   analyse(text, alphabet);
   for(int i = 0; i < 26; i++)
      cout << char(i + 65) << " : " << alphabet[i] << "\n";
   */

   /*
   test de la conversion vers d'autre bases :
   */
   int nb = 0, base = 0, base2 = 0;
   cin >> nb >> base >> base2;
   cout << nb << " en base " << base << " : " << versAutreBase(nb, base) << "\n";
   cout << text << " ( en base " << base2 << ") en base 10 : " << versBaseDix(text, base2);
   

   return EXIT_SUCCESS;
}
