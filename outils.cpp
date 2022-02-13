//#include "outils.h"
#include <cctype>
#include <iostream>
#include <ostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

float SQRT_5 = 2.236067977499789696409173668731;

// std::string CARACTERESSPECIAUX =" '.,;(){}\"\\?/!:&#%$£_-+*|@0123456789\n";
// int TAILLE_CARSPEC = CARACTERESSPECIAUX.length()

std::string supprimerAccents(std::string message)
{
    std::string accent("ÀÁÂÃÄÅàáâãäåÒÓÔÕÖØòóôõöøÈÉÊËèéêëÌÍÎÏìíîïÙÚÛÜùúûüÿÑñÇç");
    std::string sansAccent("AAAAAAaaaaaaOOOOOOooooooEEEEeeeeIIIIiiiiUUUUuuuuyNnCc");
    int i=0,j=0,k=0,taille;

    taille=message.size();

    for (i=0;i<=taille;i++)
    {
        for(j=0;j<=104;j=j+2)
        {
            if((message[i]==accent[j])&&(message[i+1]==accent[j+1]))
            {
                message[i]=sansAccent[j/2];
                for(k=i+1;k<taille;k++)
                {
                    message[k]=message[k+1];
                }
                message=message.substr(0,taille-1);
                taille=message.size();
            }
        }
    }

    return message;
}

std::string metttreMaj(std::string message)
{
   std::string messageFinal = "";
   for(int i = 0; i < (int)(message.length()); i++)
      messageFinal += std::toupper(message[i]);
   return messageFinal;
}

// Ne garde que les lettres d'un message
std::string garderLettres(std::string message)
{
   std::string text = "";
   for (int i = 0; i < int(message.length()); i++)
      if (isalpha(message[i]))
         text += toupper(message[i]);

   return text;
}

// Met des majuscules au bédut des phrases
std::string jolitexte(std::string text)
{
   text[0] = toupper(text[0]);
   text[1] = tolower(text[1]);
    for(int nb=2; nb < ((int)(text.length()) ); nb++)
        if( (text[nb-1] == '.' || text[nb-1] == '?' || text[nb-1] == '!' ) || (text[nb - 1] == ' ' && (text[nb-2] == '.' || text[nb-2] == '?' || text[nb-2] == '!')) )
            text[nb] = toupper(text[nb]);
        else
            text[nb] = tolower(text[nb]);
    return text;

   /*std::string textFinal = "" ;
    for(int nb=2; nb < ((int)(text.length()) ); nb++)
        if( (text[nb-1] == '.' || text[nb-1] == '?' || text[nb-1] == '!' ) || (text[nb - 1] == ' ' && (text[nb-2] == '.' || text[nb-2] == '?' || text[nb-2] == '!')) )
            textFinal += toupper(text[nb]);
         else
            textFinal += tolower(text[nb]);
    return textFinal; */
}

// Returns the addition of the two uppercase letters (A=0, ..., Z=25)
char addl(char l, char l2 )
{
    // we add the ascii numbers (it starts at A=65, but it's not a problem because 2*65=130=0[26) then we take this modulo 26 and finaly we add 65 to get a letter 
    return (char)((((int)(l) + (int)(l2)) % 26) + 65);
}

// Retourne le texte crypté avec le code vigenere avec le mot
std::string codagev(std::string text, std::string mot)
{
    mot = metttreMaj(supprimerAccents(mot));
    text = metttreMaj(supprimerAccents(text));

    int nb2 = mot.length();
    std::string textCode = "";

    int nb4 = 0; // compte du nombre de lettres déjà cryptées dans le texte

    for (int nb3 = 0 ; nb3 < (int)(text.length()); nb3++)
    {
        if(text[nb3] > 64 && text[nb3] < 91)
        {
           textCode += addl(text[nb3], mot[(nb4 % nb2)]);
           nb4 ++;
        }
        else
           textCode += text[nb3];
    }
    return textCode;
}

// Returns the substraction of the two uppercase letters (A=0, ..., Z=25)
char sousl(char l, char l2 )
{
    // we add the ascii numbers (it starts at A=65, but it's not a problem because 65-65=0[26) then we take this modulo 26 and finaly we add 65 to get a letter 
    return (char)((((int)(l) - (int)(l2) + 26) % 26) + 65);
}

// Retourne le texte décrypté avec le code vigenere avec le mot
std::string decodagev(std::string text, std::string mot)
{
    mot = metttreMaj(supprimerAccents(mot));
    text = metttreMaj(supprimerAccents(text));

    int nb2 = mot.length();
    std::string textCode = "";

    int nb4 = 0; // compte du nombre de lettres déjà cryptées dans le texte

    for (int nb3 = 0 ; nb3 < (int)(text.length()); nb3++)
    {
        if(text[nb3] > 64 && text[nb3] < 91)
        {
           textCode += sousl(text[nb3], mot[(nb4 % nb2)]);
           nb4 ++;
        }
        else
           textCode += text[nb3];
    }
    return textCode;
}

// Retourne les cles potentiellement utilisées pour chiffrer le message avec vigenère
// std::string decodage_automatique_v(std::string text, int TAILLE_MAX = 20, int FREQ_MIN = 10)
std::string decodage_automatique_v(std::string text, int TAILLE_MAX = 20)
{
   // On ne garde que les lettres (on s'en fiche du reste)
   text = garderLettres(text);

   // Liste des mots qui sont peut-être des cles en fonction de la taille de la cle
   std::string mots_possibles[TAILLE_MAX];
   for (int i = 0; i < TAILLE_MAX; i ++)
      mots_possibles[i] = "";
      
   // probable[a] dit si la cle est preobablement de longueur a
   // bool probable[TAILLE_MAX];
   // for (int i = 0; i < TAILLE_MAX; i ++)
   //   probable[i] = true;

   // pour chaque longueur de cle, on regarde quelle est la plus petite fréquence de 'e'
   double freq_e_min[TAILLE_MAX];
   freq_e_min[0] = 0;
   for(int i = 1; i < TAILLE_MAX; i++)
      freq_e_min[i] = 100;

   int longueur = text.length();

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
            compte[text[i*a+j]-'A'] ++;

         // Nombre total de lettre dans la partie et lettre la plus frequente
         int tot = 0;
         int max = 0;
         int max_pos = 0;

         for (int a = 0; a<26;a++)
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

         // Si elle est pas assez fréquente, c'est sûrement pas la bonne longueur de clé
         // if (freq_max < FREQ_MIN)
         //   probable[i] = false;

         // On ajoute la lettre telle que si l'on décode la lettre la plus fréquente avec celle ci, on obtienne un E
         mots_possibles[i] += char((max_pos - 4 + 26) % 26 + 'A');
      }
   }

   // for(int i = 0; i < TAILLE_MAX; i ++)
   //    if (probable[i])
   //    {
   //       return mots_possibles[i];
   //    }

   double max = 0;
   int max_pos = 0;

   for (int a = 0; a < TAILLE_MAX; a++)
      if (freq_e_min[a] > max)
      {
         max = freq_e_min[a];
         max_pos = a;
      }

   // for (int a = 0; a < TAILLE_MAX; a++)
   //   std::cout << mots_possibles[a] << " : " << freq_e_min[a] << std::endl;

   return mots_possibles[max_pos];
}

void kasiski_test(std::string text, std::vector<int> & distance, int taille = 3)
{
    std::vector<std::string> sequences;
    text = garderLettres(supprimerAccents(text));

    for(int i = 0; i < int(text.length()) - taille; i++)
        sequences.push_back(text.substr(i, taille));
        //sequences.push_back(std::to_string(text[i]) + std::to_string(text[i+1]) + std::to_string(text[i+2]));
    
    for(int i = 0; i < int(sequences.size()) - 1; i++)
    {
        for(int j = i+1; j < int(sequences.size()); j++)
        {
            if(sequences[i] == sequences[j])
            {
                distance.push_back(j-i);
                //std::cout << j-i << " : " << sequences[i] << std::endl;
            }
        }
    }
}

int get_key_length(std::string text)
{
    std::vector<int> distances;
    for(int seqLen = 5; seqLen >= 3; seqLen--)
    {
        kasiski_test(text, distances, seqLen);

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

std::string get_key(std::string text)
{
    int taille_clef = get_key_length(text);
    text = garderLettres(metttreMaj(supprimerAccents(text)));
    std::string clef = "";

    // On découpe le texte en taille_clef parties (codés différement car la clef a taille_clef lettres)
      for(int j = 0; j < taille_clef; j++)
      {
         // Compte le nombre d'apparition de chaque lettre
         int compte[26];
         for (int a = 0; a < 26; a++)
            compte[a] = 0;

         for(int a = 0; taille_clef*a+j < int(text.length()); a++)
            compte[text[taille_clef*a+j]-'A'] ++;

         // Nombre total de lettre dans la partie et lettre la plus frequente
         int tot = 0;
         int max = 0;
         int max_pos = 0;

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

// Retourne l'analyse de fréquences des lettres (en majuscule) dans un texte
std::string analyse(std::string text)
{
     text = metttreMaj(supprimerAccents(text));
     std::string Analyse = "Nombre total de caractères : ";
     int nb = text.length();
     int liste[26];

     for (int nb2 = 0; nb2 < 26; nb2++)
         liste[nb2] = 0;

     for (int nb2 = 0; nb2 < nb; nb2++)
        if(text[nb2] > 64 && text[nb2] < 91)
            liste[(int)(text[nb2]) - 65] ++;

     nb = 0;

     for (int nb2 = 0; nb2 < 26; nb2++)
         nb += liste[nb2];

     std::string truc = std::to_string(nb);
     Analyse = Analyse + truc + "\n";

     for (int nb2 = 0; nb2 < 26; nb2++)
         if ( liste[nb2] != 0)
         {
             char lettre = nb2 + 65;
             std::string nbtotalcaractere = std::to_string(liste[nb2]);
             std::string pourcentagecaractere = std::to_string(100 * (float)(liste[nb2]) / (float)(nb));
             Analyse = Analyse + "\n" + lettre + " : " + nbtotalcaractere + " soit environ " + pourcentagecaractere + " %";
         }
     
    return Analyse;
}

// Retourne le nombre d'occurence de chacune des lettres de l'alphabet
void analyse(std::string text, std::vector<int> & alphabet)
{
     text = metttreMaj(supprimerAccents(text));

     for (int nb2 = 0; nb2 < 26; nb2++)
        alphabet.push_back(0);

     for (int nb2 = 0; nb2 < int(text.length()); nb2++)
        if(std::isalpha(text[nb2]))
            alphabet[(int)(text[nb2]) - 65] ++;
}

double index_of_coincidence(std::string text)
{
    text = garderLettres(supprimerAccents(text));
    int l = text.length();

    std::vector<int> alphabet;
    analyse(text, alphabet);

    int index_of_coincidence = 0;

    for(int i = 0; i < 26; i++)
    {
        index_of_coincidence += alphabet[i] * (alphabet[i] - 1);

    }

    return double(index_of_coincidence) / double((l)*(l-1));
}

//int get_key_length_ioc(std::string text)
//{

//}

// Codage par substitution (on entre le text + la substitution (=
/*
std::string codages()
{
    std::string mot = m_texte.toStdstd::string();

    mot = this->supprimerAccents(mot);

    std::string textCode = "";

    for(int nb = 0; nb < (int)(mot.length()); nb++)
    {
        std::string caracteresspeciaux =" '.,;(){}\"\\?/!:0123456789\n";
        bool isspecial = false;
        for(int nb8=0; nb8 < (int)(caracteresspeciaux.length()); nb8++)
        {
            if(mot[nb] == caracteresspeciaux[nb8])
                isspecial = true;
        }
        mot[nb] = toupper(mot[nb]);
        int lettre = mot[nb] - 'A';
        if( isspecial || (m_lettresubstitution[lettre] == '\0') )
          textCode = textCode + mot[nb];
        else
          textCode = textCode + m_lettresubstitution[lettre];
    }

    return textCode;
}*/

std::string versAutreBase(int nb, int base)
{
   std::string nbFinal = "";
    int nb2 = 1;
    while(pow(base, nb2) < nb)
    {
        nb2++;
    }
    while(nb2 >= 0)
    {
        int nb5 = pow(base, nb2);
        char nouveaunombre = '\0';

        if( nb / nb5 > 9)
            nouveaunombre = (nb / nb5) - 10 + 'a';
        else if( nb / nb5 < 10)
             nouveaunombre = (nb / nb5) + '0';
        else
            return "-1";

        nbFinal = nbFinal + nouveaunombre;

        nb = nb % nb5;

        nb2--;
    }
    if(nbFinal[0] == '0')
    {
        nbFinal=nbFinal.substr(1,(int)(nbFinal.length()));
    }
    return nbFinal;
}
int versBaseDix(std::string nb, int base)
{
    int nouveauNombre = 0;
    for(int nb2 = 0; nb2 < (int)(nb.length()); nb2++)
    {
        if(nb[nb2] >= 'a' && nb[nb2] <= 'z')
            nouveauNombre += (nb[nb2] - 'a' + 10) * pow(base, (int)(nb.length()) - 1 - nb2);
        else if(nb[nb2] >= '0' && nb[nb2] <= '9')
            nouveauNombre += (nb[nb2] - '0') * pow(base, (int)(nb.length()) - 1 - nb2);
        else
            return -1;
    }
    return nouveauNombre;
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

void factprems(unsigned long long int nb, std::vector<int> & factprems)
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

void diviseurs(unsigned long long int nb,std::vector<int> & diviseurs)
{
   std::string messageDiviseurs = "";

    if(nb <= 1)
    {
      int a = 2;
      a++;
    }
    else if (estPrems(nb))
    {
       diviseurs.push_back(1);
       diviseurs.push_back(nb);
    }
    else
    {
        // On stocke tous les diviseurs de nb dans un vecor (nommé diviseurs)
       std::vector<int> diviseurs;
        for(unsigned long long int nb2 = 1; nb2 <= nb; nb2 ++)
            if (nb % nb2 == 0)
                diviseurs.push_back(nb2);
   }
// Pour trier un vecteur :        sort(facteurs_prems.begin(), facteurs_prems.end());
}

// Stoque dans lestd::vector nbsprems les nombres premiers de 1 à N
void NbsPremsjusquaN(unsigned long long int N,std::vector<int> & nbsprems)
{
     // on ajoute déjà 2
     nbsprems.push_back(2);

     // on fait une boucle de 3 à N de 2 en 2 pour trouver tous les nombres premiers (car les nombres pairs différents de 2 ne sont pas premiers)
     for(unsigned long long int nb = 3; nb <= N; nb += 2)
     {
         bool estprems = true;
         unsigned long long nb2 = 0;

         unsigned long long int sqrt_num = (int)(sqrt(nb));


         // Si le nombre n'est premier on s'arrête, si on a atteint la fin de la liste des nombres premiers (nb2 > nbsprems.size()), on s'arre, si il n'est divisible par aucun nombre permier inférieur ou égal à sa racine carré, on arrête aussi
         while (estprems && (nb2 < (unsigned long long int)(nbsprems.size())) && ((unsigned long long int)(nbsprems[nb2]) <= sqrt_num))
         {
             if (nb % nbsprems[nb2] == 0)
                 estprems = false;
             nb2 ++;
         }

         if (estprems)
             nbsprems.push_back(nb);
     }
}

// Stoque dans lestd::vector nbsprems les N premiers nombres premiers
void NpremsNbsprems(unsigned long long int N,std::vector<int> & nbsprems)
{
     // compte des nombres premiers
     unsigned long long int num = 1;

     // on ajoute déjà 2
     nbsprems.push_back(2);

     // même boucle que dans NbsPremsjusquaN sauf que la condition pour continuer est différente : c'est que num (le compte du nombre de nombres premiers) spot inférieur au nombre de nombres premiers que l'on veut à la fin
     for(unsigned long long int nb = 3; num < N; nb += 2)
     {
         bool estprems = true;
         int nb2 = 0;

         unsigned long long int sqrt_num = (int)(sqrt(nb));


         while (estprems && (nb2 < (int)(nbsprems.size())) && ((unsigned long long int)(nbsprems[nb2]) <= sqrt_num))
         {
             if (nb % nbsprems[nb2] == 0)
                 estprems = false;
             nb2 ++;
         }

         if (estprems)
         {
            nbsprems.push_back(nb);
            num++;
         }
     }
}

// Retourne le terme nb de la suite de fibonacci
long long int fibo(int nb)
{
   return int((pow(1+SQRT_5, nb)-pow(1-SQRT_5, nb))/(pow(2,nb)*SQRT_5));
}
// The same but maybe faster and not as precise
/*unsigned long long int fibo2(int nb)
{
   return int((pow(1+SQRT_5, nb))/(pow(2,nb)*SQRT_5));
}*/

// returns a fraction that is the approximation of a decimal number
std::string farey_approximation(float nb, int max_precision = 1000000)
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
long double approximation_racinecubique(int nb, int precision = 40)
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
long double approximation_racinecarre(int nb, int precision = 40)
{
   long double approximation = 0;
   while(approximation*approximation<= nb)
      approximation++;
   approximation--;
   if(approximation*approximation== nb)
      return approximation;

   for(int i = 0; i < precision; i++)
      approximation += (nb - approximation*approximation) / (2*approximation);

   return approximation;

}
