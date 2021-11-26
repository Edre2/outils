# Outils
Quelques outils en cpp (par exemple : crypter/décrypter avec le chiffrement vigenère, savoir si un nombre est premier...)

# L'utiliser :
Dans votre fichier .cpp, écrivez la ligne `#include "outils.cpp"`

# Fonctions disponibles
Voici les fonctions disponibles :
```
std::string supprimerAccents(std::string message);   // Supprime tous les accents du message
std::string metttreMaj(std::string message);    // Met tout le texte en majuscules
std::string jolitexte(std::string text);   // Met tout le texte en minucules et met des majuscules au début des phrase

char addl(char l, char l2 );   // Additionne deux caractères (utilisé dans codagev)
std::string codagev(std::string text, std::string mot);   // Code un texte avec le chiffrement vigenère à l'aide du mot
char sousl(char l, char l2 );   //  Soustrait deux caractères (utilisé dans decodagev)
std::string decodagev(std::string text, std::string mot);   // Déode un texte avec le chiffrement vigenère à l'aide du mot

// std::string codages(); // Pas encore prêt
// std::string decodages(); // Pas encore prêt

std::string analyse(std::string text); // Retourne une analyse du texte sous forme de texte
void analyse(std::string text, std::vector<int> & alphabet)  // Retourne une le nombre d'ocurence de chaque lettre dans un vector

std::string versAutreBase(int nb, int base); // Convertit un nombre de la base 10 vers la base 'base'
int versBaseDix(std::string nb, int base); // Convertit un nombre de la base 'base' vers la base 10

bool estPrems(unsigned long long int nb);     // Retourne si un nombre est premier
void factprems(unsigned long long int nb, std::vector<int> & factprems);     // Retourne les facteurs premiers d'un nombre dans le vector 'factprems'
void diviseurs(unsigned long long int nb, std::vector<int> & diviseurs);    // Pas fini

void NbsPremsjusquaN(unsigned long long int N, std::vector<int> & nbsprems);    // Retourne tous les nombres premiers jusqu'à N dans le vector nbsprems
void NpremsNbsprems(unsigned long long int N, std::vector<int> & nbsprems);     // Retourne les N premiers nombres premiers dans le vector nbsprems
```
