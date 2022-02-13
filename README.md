# Outils
Quelques outils en `c++`, `python` et `javascript`. \
Il y a surtout des fonctions : 
- pour faire de la cryptographie  crypter/décrypter avec le chiffrement vigenère, décrypter automatiquement...)
- savoir si un nombre est permies, approximer un nombre réel avec une fraction (en `c++` seulement)

# L'utiliser :
Dans votre fichier en `c++`, écrivez la ligne `#include "outils.cpp"` \
Dans un ficher en `pyhton`, ajoutez `import * from outils` \
En `javascript` il devrait y avoir un moyen de faire la même chose mais je ne sais pas comment faire, donc copiez/collez tout le contenu dans votre fichier si vous ne savez pas non plus. 

# Exemple
Un exemple d'utilisation en `javascript` est disponibla sur [ce site](https://edre2.github.io/codage/codage.html) \
EN `c++`, vous pouvez jeter un oeil à `test.cpp` (tout est commenté, libre à vous de décommenter ce que vous voulez pour faire des tests, des textes codés avec vigenère ainsi que la clé utilisée sont inclus) \
En `pyhton`, débrouillez vous.

# Fonctions disponibles
Voici les fonctions disponibles : (elles ssont listées en `c++` mais les même sont (quasiment toutes) disponibles en `python` et `javascript`)
``` cpp
std::string supprimerAccents(std::string message);   // Supprime tous les accents du message
std::string metttreMaj(std::string message);    // Met tout le texte en majuscules
std::string jolitexte(std::string text);   // Met tout le texte en minucules et met des majuscules au début des phrase
std::string garderLettres(std::string message); // Ne garde que les lettres d'un messga


char addl(char l, char l2 );   // Additionne deux caractères (utilisé dans codagev)
std::string codagev(std::string text, std::string mot);   // Code un texte avec le chiffrement vigenère à l'aide du mot
char sousl(char l, char l2 );   //  Soustrait deux caractères (utilisé dans decodagev)
std::string decodagev(std::string text, std::string mot);   // Déode un texte avec le chiffrement vigenère à l'aide du mot

std::string decodage_automatique_v(std::string text, int TAILLE_MAX = 20); // Retourne les cles potentiellement utilisées pour chiffrer le message avec vigenère
void kasiski_test(std::string text, std::vector<int> & distance, int taille = 3); // Retourne les distances entre les apparitions de bout de texte pareils (de longueur taille)
int get_key_length(std::string text); // Utilise le test de kasiki pour trouver la longueur de le cle
std::string get_key(std::string text); // Utilise get_key_length puis trouve la cle avec la fréquence des 'e'

// std::string codages(); // Pas encore prêt
// std::string decodages(); // Pas encore prêt

std::string analyse(std::string text); // Retourne une analyse du texte sous forme de texte
void analyse(std::string text, std::vector<int> & alphabet)  // Retourne une le nombre d'ocurence de chaque lettre dans un vector
double index_of_coincidence(std::string text); // Calcule l'index of coincidence d'un texte

std::string versAutreBase(int nb, int base); // Convertit un nombre de la base 10 vers la base 'base'
int versBaseDix(std::string nb, int base); // Convertit un nombre de la base 'base' vers la base 10

bool estPrems(long long nb);     // Retourne si un nombre est premier
bool estprems_big(boost::multiprecision::cpp_int nb); // Retourne si un vraiment grand nombre est premier
void factprems(unsigned long long int nb, std::vector<int> & factprems);     // Retourne les facteurs premiers d'un nombre dans le vector 'factprems'
void diviseurs(unsigned long long int nb, std::vector<int> & diviseurs);    // Pas fini

void NbsPremsjusquaN(unsigned long long int N, std::vector<int> & nbsprems);    // Retourne tous les nombres premiers jusqu'à N dans le vector nbsprems
void NpremsNbsprems(unsigned long long int N, std::vector<int> & nbsprems);     // Retourne les N premiers nombres premiers dans le vector nbsprems

long long int fibo(int nb); //Retourne le terme nb de la suite de fibonacci
std::string farey_approximation(float nb, int max_precision = 1000000); // retourne une fraction (de la forme "45/67") qui est une approximation d'un nombre réel (à virgule)
long double approximation_racinecubique(int nb, int precision = 40); // retourne une approximation de la racine cubique
long double approximation_racinecarre(int nb, int precision = 40); // retourne une approximation de la racine carré
```
