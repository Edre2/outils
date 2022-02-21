# Outils
Quelques outils en `c++`, `python` et `javascript`. \
Il y a surtout des fonctions : 
- pour faire de la cryptographie  crypter/décrypter avec le chiffrement vigenère, décrypter automatiquement...)
- savoir si un nombre est permies, approximer un nombre réel avec une fraction (en `c++` seulement)
- calculer une expression (par exemple `32*(48+2)-23^2`)

# L'utiliser :
- Dans votre fichier en `c++`, écrivez la ligne `#include "outils.h"`. \
Pour l'éxecuter dans un IDE, ça devrait marcher tour seul. \
Pour éxécuter votre code avec `g++`, vous devrez alors entrer les commandes (sous Linux) :
``` bash
g++ -c outils.cpp -O2 - Wall -Wextra -Werror
g++ -c test.cpp -O2 - Wall -Wextra -Werror
g++ outils.o test.o -o NomDuProgramme
./NomDuProgramme
```
Vous pouvez faire un script bash :
``` bash
#!/bin/bash

for var in "$@"
do
   g++ -c "$var" -O2 - Wall -Wextra -Werror
done

g++ *.o -o truc
./truc
rm truc
rm *.o
```
Puis définir un alias pour le lancer (par exemple `cpp`), pour compiler et exécuter le code, vous n'aurez plus qu'à lancer : 
```bash
cpp outils.cpp test.cpp
```
PLus simplement, cette commande marche également (mais elle est moins générale):
``` bash
 g++ -c outils.cpp && g++ -c test.cpp && g++ -o test outils.o test.o && ./test
```
Et le script supprimera également les fichiers créés à l'occasion. 
- Dans un ficher en `pyhton`, ajoutez `import * from outils`. 
- En `javascript` il devrait y avoir un moyen de faire la même chose mais je ne sais pas comment faire, donc copiez/collez tout le contenu dans votre fichier si vous ne savez pas non plus. 

# Exemple
Un exemple d'utilisation en `javascript` est disponible sur [ce site](https://edre2.github.io/codage/codage.html) pour la partie cryptographie et [ce site](https://edre2.github.io/nombres/nombres.html) pour la partie sur les nombres.\
En `c++`, vous pouvez jeter un oeil à `test.cpp` (tout est commenté, libre à vous de décommenter ce que vous voulez pour faire des tests, des textes codés avec vigenère ainsi que la clé utilisée sont inclus). \
En `pyhton`, débrouillez vous (c'est pas très compliqué).

# Fonctions disponibles
Voici les fonctions disponibles : 
- en `c++` :
``` cpp
// PARTIE SUR LES TEXTES

std::string supprimerAccents(std::string message);   // Supprime tous les accents du message
std::string metttreMaj(std::string message);    // Met tout le texte en majuscules
std::string jolitexte(std::string texte);   // Met tout le texte en minucules et met des majuscules au début des phrase
std::string garderLettres(std::string message); // Ne garde que les lettres d'un messga

int indexFromString(std::string texte, char caractere);

double index_of_coincidence(std::string texte); // Calcule l'index of coincidence d'un texte

void split(std::string texte, char separator, std::vector<std::string> & texte_split); // split le texte autour du separateur
void split_multiple_char(std::string texte, std::string separators, std::vector<std::string> & texte_split);

char addl(char l, char l2 );   // Additionne deux caractères (utilisé dans codagev)
char sousl(char l, char l2 );   //  Soustrait deux caractères (utilisé dans decodagev)
std::string codagev(std::string texte, std::string mot);   // Code un texte avec le chiffrement vigenère à l'aide du mot
std::string decodagev(std::string texte, std::string mot);   // Déode un texte avec le chiffrement vigenère à l'aide du mot

std::string decodage_automatique_v(std::string texte, int TAILLE_MAX = 20); // Retourne les cles potentiellement utilisées pour chiffrer le message avec vigenère
void kasiski_test(std::string texte, std::vector<int> & distance, int taille = 3); // Retourne les distances entre les apparitions de bout de texte pareils (de longueur taille)
int get_key_length(std::string texte); // Utilise le test de kasiki pour trouver la longueur de le cle
std::string get_key(std::string texte); // Utilise get_key_length puis trouve la cle avec la fréquence des 'e'

std::string codages(std::string texte, std::string substitution); // Code un texte avec le chiffrement par substitution (a devient la 1ère lettre de substitution, b la 2ème ...)
std::string decodages(std::string texte, std::string substitution); // Décode un texte avec le chiffrement par substitution (a devient la 1ère lettre de substitution, b la 2ème ...)

std::string analyse(std::string texte); // Retourne une analyse du texte sous forme de texte
void analyse(std::string texte, std::vector<int> & alphabet);  // Retourne une le nombre d'ocurence de chaque lettre dans un vector


// PARTIE SUR LES NOMBRES

std::string convertBase(std::string value, int from_base, int to_base); // convertit un nombre d'une base vers une autre

bool estPrems(long long nb);     // Retourne si un nombre est premier
void factprems(long long int nb, std::vector<int> & factprems);     // Retourne les facteurs premiers d'un nombre dans le vector 'factprems'
void diviseurs(long long int nb, std::vector<int> & diviseurs);    // Pas fini

void NbsPremsjusquaN(long long int N, std::vector<int> & nbsprems);    // Retourne tous les nombres premiers jusqu'à N dans le vector nbsprems
void NpremsNbsprems(long long int N, std::vector<int> & nbsprems);     // Retourne les N premiers nombres premiers dans le vector nbsprems

long long int fibo(int nb); //Retourne le terme nb de la suite de fibonacci
std::string farey_approximation(float nb, int max_precision = 1000000); // retourne une fraction (de la forme "45/67") qui est une approximation d'un nombre réel (à virgule)
long double approximation_racinecubique(int nb, int precision = 40); // retourne une approximation de la racine cubique
long double approximation_racinecarre(int nb, int precision = 40); // retourne une approximation de la racine carré


// CALCULATRICE

enum class Associativite {droite, gauche, indefini};
long double op(long double nb1, long double nb2, char operateur); // calcule l'opération entre nb1 et nb2
int operateur_priorite(std::string operateur);
Associativite operateur_associativite(std::string operateur);
bool isNumber(const std::string& str);


long double calculer_notation_polonaise_inversee(std::string calcul);
long double calculer(std::string calcul);

long double eval(std::string calcul); // calule le calcul
```
- en `python` :
``` py
# Met toutes les lettres du texte en majuscules et enlève les accents et les espaces et la ponctuation
removeAll(texte : str, to_remove: str)
# Enlève les caractères de remove et les accents
format(texte :str, remove=" ,;:!?.()[]{}-+=*\n")
# Retourne la lettre la plus fréquente du texte
plus_frequente(texte: str)
# Ne garde que les lettres d'un message
garderLettres(texte :str)
# Une fonction qui crypte un texte avec le code de César en décalant les lettres de l'alphabet de n
crypt_c(texte :str, n :int)
# Une fonction qui decrypte un texte avec le code de César en décalant les lettres de l'alphabet de n
decrypt_c(texte :str, n :int)
# Décode automatiquement un code césar
decodage_automatique_c(texte :str)
# Une fonction qui crypte un texte avec le code Vigenère et le mot
crypt_v(texte :str, mot :str)
# Une fonction qui crypte un texte avec le code Vigenère et le mot
decrypt_v(texte :str, mot :str)
# Une fonciton qui décrypte automatiquement un message chiffré avec vigenère
decodage_automatique_v(texte :str, TAILLE_MAX = 20)
# A function that returns if a number is a prime number or not
isprime(nb :int)
# A function that returns the prime numbers until 2 000 000 by reading a file that already has them
primeNbs()
# A function that returns the prime factors of an integer 
primeFacts(nb :int)
# Retourne les nombres premiers jusqu'à n
NbsPremsjusquaN(n :int)
```

- en `javascript` :
``` js
supprimerAccents(message)
mettreMaj(message)
garderLettres(message)
addl(char1, char2)
sousl(char1, char2) 
codagev(message, mot)
decodagev(message, mot) 
decodage_automatique_v(message, taille_max = 20)
analyse(message)
convertBase(value, from_base, to_base) 
estPrems(n)
diviseurs(nombre)
NbsPremsjusquaN(nombre)
farey_approximation(nombre, precision)
pgcd(a,  b)
```

# TODO
- implémenter `int get_key_length_ioc(std::string texte)` en `c++` (puis dans les autres languages)