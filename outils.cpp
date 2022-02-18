#include "outils.h"

float SQRT_5 = 2.236067977499789696409173668731;

// std::string CARACTERESSPECIAUX =" '.,;(){}\"\\?/!:&#%$£_-+*|@0123456789\n";



////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////// PARTIE SUR LES TEXTES /////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

std::string supprimerAccents(std::string message)
{
    std::string accent("ÀÁÂÃÄÅàáâãäåÒÓÔÕÖØòóôõöøÈÉÊËèéêëÌÍÎÏìíîïÙÚÛÜùúûüÿÑñÇç");
    std::string sansAccent("AAAAAAaaaaaaOOOOOOooooooEEEEeeeeIIIIiiiiUUUUuuuuyNnCc");

    int i = 0, j = 0, k = 0, taille = message.size();

    for (i = 0; i <= taille; i++)
    {
        for(j = 0; j <= 104; j+=2)
        {
            if((message[i] == accent[j]) && (message[i+1] == accent[j+1]))
            {
                message[i] = sansAccent[j/2];
                
                for(k = i+1; k < taille; k++)
                    message[k] = message[k+1];

                message = message.substr(0,taille-1);
                taille = message.size();
            }
        }
    }

    return message;
}

std::string mettreMaj(std::string message)
{
   std::string messageFinal = "";
   for(int i = 0; i < (int)(message.length()); i++)
      messageFinal += std::toupper(message[i]);
   return messageFinal;
}

// Ne garde que les lettres d'un message
std::string garderLettres(std::string message)
{
   std::string texteCode = "";
   for (int i = 0; i < int(message.length()); i++)
      if (isalpha(message[i]))
         texteCode += toupper(message[i]);

   return texteCode;
}

// Met des majuscules au bédut des phrases
std::string jolitexte(std::string texte)
{
   texte[0] = toupper(texte[0]);
   texte[1] = tolower(texte[1]);

    for(int i = 2; i < (int)(texte.length()); i++)
        if( (texte[i-1] == '.' || texte[i-1] == '?' || texte[i-1] == '!' ) || (texte[i - 1] == ' ' && (texte[i-2] == '.' || texte[i-2] == '?' || texte[i-2] == '!')) )
            texte[i] = toupper(texte[i]);
        else
            texte[i] = tolower(texte[i]);

    return texte;
}

int indexFromString(std::string texte, char caractere)
{
    auto res = find (texte.begin(), texte.end(), caractere);
    return int(res - texte.begin());
}


double index_of_coincidence(std::string texte)
{
    texte = garderLettres(supprimerAccents(texte));
    int l = texte.length();

    std::vector<int> alphabet;
    analyse(texte, alphabet);

    int index_of_coincidence = 0;

    for(int i = 0; i < 26; i++)
        index_of_coincidence += alphabet[i] * (alphabet[i] - 1);

    return double(index_of_coincidence) / double((l)*(l-1));
}

// Codage vigenère : 

// Returns the addition of the two uppercase letters (A=0, ..., Z=25)
char addl(char l, char l2 )
{
    // we add the ascii numbers (it starts at A=65, but it's not a problem because 2*65=130=0[26) then we take this modulo 26 and finaly we add 65 to get a letter 
    return char(((int(l) + int(l2))% 26) + 65);
}

// Returns the substraction of the two uppercase letters (A=0, ..., Z=25)
char sousl(char l, char l2 )
{
    // we add the ascii numbers (it starts at A=65, but it's not a problem because 65-65=0[26) then we take this modulo 26 and finaly we add 65 to get a letter 
    return (char)((((int)(l) - (int)(l2) + 26) % 26) + 65);
}

// Retourne le texte crypté avec le code vigenere avec le mot
std::string codagev(std::string texte, std::string mot)
{
    mot = mettreMaj(supprimerAccents(mot));
    texte = mettreMaj(supprimerAccents(texte));

    int length_mot = mot.length();
    std::string texteCode = "";

    int nb_lettres_codees = 0; // compte du nombre de lettres déjà cryptées dans le texte

    for (int i = 0 ; i < (int)(texte.length()); i++)
    {
        if(isalpha(texte[i]))
        {
           texteCode += addl(texte[i], mot[(nb_lettres_codees % length_mot)]);
           nb_lettres_codees ++;
        }
        else
           texteCode += texte[i];
    }
    return texteCode;
}

// Retourne le texte décrypté avec le code vigenere avec le mot
std::string decodagev(std::string texte, std::string mot)
{
    mot = mettreMaj(supprimerAccents(mot));
    texte = mettreMaj(supprimerAccents(texte));

    int length_mot = mot.length();
    std::string texteCode = "";

    int nb_lettres_codees = 0; // compte du nombre de lettres déjà cryptées dans le texte

    for (int i = 0 ; i < (int)(texte.length()); i++)
    {
        if(texte[i] > 64 && texte[i] < 91)
        {
           texteCode += sousl(texte[i], mot[nb_lettres_codees % length_mot]);
           nb_lettres_codees ++;
        }
        else
           texteCode += texte[i];
    }
    return texteCode;
}

// Retourne les cles potentiellement utilisées pour chiffrer le message avec vigenère
std::string decodage_automatique_v(std::string texte, int TAILLE_MAX)
{
   // On ne garde que les lettres (on s'en fiche du reste)
   texte = garderLettres(texte);

   // Liste des mots qui sont peut-être des cles en fonction de la taille de la cle
   std::string mots_possibles[TAILLE_MAX];
   // pour chaque longueur de cle, on regarde quelle est la plus petite fréquence de 'e'
   double freq_e_min[TAILLE_MAX];

   for (int i = 0; i < TAILLE_MAX; i ++)
   {
      mots_possibles[i] = "";
      freq_e_min[i] = 100;
   }
      
   int longueur = texte.length();

   // On teste toutes les longueurs de clés jusqu'à TAILLE_MAX pour voir si les fréquences correspondent au français
   for(int i = 1; i < TAILLE_MAX; i++)
   {
      // On découpe le texte en i parties (codés différement car la clef a i lettres)
      for(int j = 0; j < i; j++)
      {
         // Compte le nombre d'apparition de chaque lettre
         int compte[26];
         for (int a = 0; a < 26; a++)
            compte[a] = 0;

         for(int a = 0; i*a+j < longueur; a++)
            compte[texte[i*a+j]-'A'] ++;

         // Nombre total de lettre dans la partie et lettre la plus frequente
         int tot = 0, max = 0, max_pos = 0;

         for (int a = 0; a < 26; a++)
         {
            tot += compte[a];
            if (compte[a] > max)
            {
               max = compte[a];
               max_pos = a;
            }
         }

         // Fréquence en pourcentage de la lettre la plus fréquente
         double freq_max = double(max) / tot * 100;

         if (freq_max < freq_e_min[i])
            freq_e_min[i] = freq_max;

         // On ajoute la lettre telle que si l'on décode la lettre la plus fréquente avec celle ci, on obtienne un E
         mots_possibles[i] += char((max_pos - 4 + 26) % 26 + 'A');
      }
   }

   double max = 0;
   int max_pos = 0;

   for (int a = 1; a < TAILLE_MAX; a++)
      if (freq_e_min[a] > max)
      {
         max = freq_e_min[a];
         max_pos = a;
      }

   return mots_possibles[max_pos];
}


void kasiski_test(std::string texte, std::vector<int> & distance, int taille)
{
    std::vector<std::string> sequences;
    texte = garderLettres(supprimerAccents(texte));

    for(int i = 0; i < int(texte.length()) - taille; i++)
        sequences.push_back(texte.substr(i, taille));
    
    for(int i = 0; i < int(sequences.size()) - 1; i++)
        for(int j = i+1; j < int(sequences.size()); j++)
            if(sequences[i] == sequences[j])
                distance.push_back(j-i);
}

int get_key_length(std::string texte)
{
    std::vector<int> distances;
    for(int seqLen = 5; seqLen >= 3; seqLen--)
    {
        kasiski_test(texte, distances, seqLen);

        if(distances.size() >= 3)
        {
            int key_length = distances[0];

            for(int i = 1; i < int(distances.size()); i++)
                key_length = std::__gcd(key_length, distances[i]);

            return key_length;
        }
    }

    if(distances.size() > 0)
    {
        int key_length = distances[0];

        for(int i = 1; i < int(distances.size()); i++)
            key_length = std::__gcd(key_length, distances[i]);

        return key_length;
    }

    return 1;
}

std::string get_key(std::string texte)
{
    int taille_clef = get_key_length(texte);
    texte = garderLettres(mettreMaj(supprimerAccents(texte)));
    std::string clef = "";

    // On découpe le texte en taille_clef parties (codés différement car la clef a taille_clef lettres)
      for(int j = 0; j < taille_clef; j++)
      {
         // Compte le nombre d'apparition de chaque lettre
         int compte[26];
         for (int a = 0; a < 26; a++)
            compte[a] = 0;

         for(int a = 0; taille_clef*a+j < int(texte.length()); a++)
            compte[texte[taille_clef*a+j]-'A'] ++;

         // Nombre total de lettre dans la partie et lettre la plus frequente
         int tot = 0, max = 0, max_pos = 0;

         for (int a = 0; a<26;a++)
         {
            tot += compte[a];
            if (compte[a] > max)
            {
               max = compte[a];
               max_pos = a;
            }
         }
         // On ajoute la lettre telle que si l'on décode la lettre la plus fréquente avec celle ci, on obtienne un E
         clef += char((max_pos - 4 + 26) % 26 + 'A');
      }

    return clef;
}

// Codage par substitution

// Code un texte avec le chiffrement par substitution (a devient la 1ère lettre de substitution, b la 2ème ...)
std::string codages(std::string texte, std::string substitution)
{
    texte = mettreMaj(supprimerAccents(texte));
    std::string texteCode = "";

    for(int i = 0; i < (int)(texte.length()); i++)
    {
        if(isalpha(texte[i]))
            texteCode += substitution[texte[i] - 65];
        else
          texteCode += texte[i];
    }

    return texteCode;
}
// Ne marche pas encore
std::string decodages(std::string texte, std::string substitution)
{
    texte = mettreMaj(supprimerAccents(texte));
    substitution = mettreMaj(substitution);
    std::string texteCode = "";

    for(int i = 0; i < (int)(texte.length()); i++)
    {
        if(isalpha(texte[i]))
        {
            texteCode += indexFromString(substitution, texte[i]) + 65;
        }
        else
          texteCode += texte[i];
    }

    return texteCode;
}

// Analyse

// Retourne l'analyse de fréquences des lettres (en majuscule) dans un texte
std::string analyse(std::string texte)
{
    std::vector<int> alphabet;
    analyse(texte, alphabet);

     int nb = texte.length();
     std::string Analyse = "Nombre total de caractères : " + std::to_string(nb) + "\n";

     for (int i = 0; i < 26; i++)
         if ( alphabet[i] != 0)
             Analyse += "\n" + std::to_string(char(i+65)) + " : " + std::to_string(alphabet[i]) + " soit environ " + std::to_string(100 * (float)(alphabet[i]) / (float)(nb)) + " %";
     
    return Analyse;
}

// Retourne le nombre d'occurence de chacune des lettres de l'alphabet
void analyse(std::string texte, std::vector<int> & alphabet)
{
     texte = mettreMaj(supprimerAccents(texte));

     for (int i = 0; i < 26; i++)
        alphabet.push_back(0);

     for (int i = 0; i < int(texte.length()); i++)
        if(std::isalpha(texte[i]))
            alphabet[(int)(texte[i]) - 65] ++;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////// PARTIE SUR LES NOMBRES ////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

std::string convertBase(std::string value, int from_base, int to_base) 
{
    std::string range = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+/";
    std::string from_range = range.substr(0, from_base);
    std::string to_range = range.substr(0, to_base);


    int dec_value = 0;
    for(int i = 0; i < int(value.length()) ; i++)
        dec_value += indexFromString(from_range, value[i]) * pow(from_base, int(value.length()) - i - 1);
    
    std::string new_value = "";
    while (dec_value > 0) {
      new_value = to_range[dec_value % to_base] + new_value;
      dec_value = (dec_value - (dec_value % to_base)) / to_base;
    }
    return new_value;
}

bool estPrems(long long nb)
{
    if(nb <= 3)
        return nb > 1;
    if(nb % 2 == 0 || nb % 3 == 0)
        return false;
    int sqrt_nb = std::sqrt(nb);
    // Les nombres premiers sont de la forme 6k+1 ou 6k-1
    // Preuve :
    // Si n % 6 = 1, alors n peut être premier
    // Si n % 6 = 0, 2, 4, alors 2 | n
    // Si n % 6 = 3, alors 3 | n
    // Si n % 6 = 5 = -1, alors n peut être premier

    // on peut ne tester que les nombres premiers <= à sqrt_n
    // (on en teste même un peu plus mais bon...)
    for (int i = 5; i <= sqrt_nb; i += 6)
       if (nb % i == 0 || nb % (i+2) == 0)
            return false;

    return true;
}

void factprems(long long int nb, std::vector<int> & factprems)
{
     while(nb % 2 == 0)
     {
         factprems.push_back(2);
         nb = nb / 2;
     }
     for(int i = 3; nb > 1; i += 2)
         while(nb % i == 0)
         {
             factprems.push_back(i);
             nb = nb / i;
         }
}

void diviseurs(long long int nb,std::vector<int> & diviseurs)
{
    if(nb > 1)
    {
        if (estPrems(nb))
        {
            diviseurs.push_back(1);
            diviseurs.push_back(nb);
        }
        else
        {
            // On stocke tous les diviseurs de nb dans un vecor (nommé diviseurs)
            std::vector<int> diviseurs;
            for(long long int i = 1; i <= nb; i ++)
                if (nb % i == 0)
                    diviseurs.push_back(i);
        }
    }
    // Pour trier un vecteur : sort(facteurs_prems.begin(), facteurs_prems.end());
}

// Stoque dans lestd::vector nbsprems les nombres premiers de 1 à N
void NbsPremsjusquaN(long long int N,std::vector<int> & nbsprems)
{
     // on ajoute déjà 2
     nbsprems.push_back(2);

     // on fait une boucle de 3 à N de 2 en 2 pour trouver tous les nombres premiers (car les nombres pairs différents de 2 ne sont pas premiers)
     for(long long int nb = 3; nb <= N; nb += 2)
     {
         bool estprems = true;

         long long int sqrt_num = (int)(sqrt(nb));

         // Si le nombre n'est premier on s'arrête, si on a atteint la fin de la liste des nombres premiers (nb2 > nbsprems.size()), on s'arre, si il n'est divisible par aucun nombre permier inférieur ou égal à sa racine carré, on arrête aussi
         for(int nb2 = 0; estprems && (long long int)(nbsprems[nb2]) <= sqrt_num
         ; nb2 ++)
             if (nb % nbsprems[nb2] == 0)
                 estprems = false;

         if (estprems)
             nbsprems.push_back(nb);
     }
}

// Stoque dans lestd::vector nbsprems les N premiers nombres premiers
void NpremsNbsprems(long long int N,std::vector<int> & nbsprems)
{
     // compte des nombres premiers
     long long int num = 1;

     // on ajoute déjà 2
     nbsprems.push_back(2);

     // même boucle que dans NbsPremsjusquaN sauf que la condition pour continuer est différente : c'est que num (le compte du nombre de nombres premiers) spot inférieur au nombre de nombres premiers que l'on veut à la fin
     for(long long int nb = 3; num <= N; nb += 2)
     {
         bool estprems = true;

         long long int sqrt_num = (int)(sqrt(nb));

         // Si le nombre n'est premier on s'arrête, si on a atteint la fin de la liste des nombres premiers (nb2 > nbsprems.size()), on s'arre, si il n'est divisible par aucun nombre permier inférieur ou égal à sa racine carré, on arrête aussi
         for(int nb2 = 0; estprems && (long long int)(nbsprems[nb2]) <= sqrt_num
         ; nb2 ++)
             if (nb % nbsprems[nb2] == 0)
                 estprems = false;

         if (estprems)
         {
             nbsprems.push_back(nb);
             num ++
         }
     }
}

// Retourne le terme nb de la suite de fibonacci
long long int fibo(int nb)
{
   return int((pow(1+SQRT_5, nb)-pow(1-SQRT_5, nb))/(pow(2,nb)*SQRT_5));
}

// returns a fraction that is the approximation of a decimal number
std::string farey_approximation(float nb, int max_precision)
{
   int nb_int = int(nb);
   float nb2 = nb - nb_int;
   int num_below = 0, den_below = 1, num_above = 1, den_above = 1, num_mediant = 1, den_mediant = 2;

   while (num_mediant < max_precision && den_mediant < max_precision)
   {
      if(nb2 > float(num_mediant)/den_mediant)
      {
         num_below = num_mediant;
         den_below = den_mediant;
         num_mediant = num_mediant + num_above;
         den_mediant = den_mediant + den_above;
      }
      else
      {
         num_above = num_mediant;
         den_above = den_mediant;
         num_mediant = num_mediant + num_below;
         den_mediant = den_mediant + den_below;
      }
   }

   return std::to_string(num_mediant + nb_int*den_mediant) + "/" + std::to_string(den_mediant);
}
// Implémentation de la formule du Héron pour approximer la racine cubique d'un nombre
long double approximation_racinecubique(int nb, int precision)
{
   long double approximation = 0;
   while(approximation*approximation*approximation <= nb)
      approximation++;
   approximation--;
   if(approximation*approximation*approximation == nb)
      return approximation;

   for(int i = 0; i < precision; i++)
      approximation += (nb - approximation*approximation*approximation) / (3*approximation*approximation*approximation);

   return approximation;
}

// Implémentation de la formule du Héron pour approximer la racine carrée d'un nombre
long double approximation_racinecarre(int nb, int precision)
{
   long double approximation = 0;
   while(approximation*approximation <= nb)
      approximation++;
   approximation--;
   if(approximation*approximation== nb)
      return approximation;

   for(int i = 0; i < precision; i++)
      approximation += (nb - approximation*approximation) / (2*approximation);

   return approximation;
}