//#include "outils.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>


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
        if(text[nb2] > 64 && text[nb2] < 91)
            alphabet[(int)(text[nb2]) - 65] ++;
}

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
}

std::string decodages()
{
    std::string mot = m_texte.toStdstd::string();

    for(int nb = 0; nb < 26; nb++)
    {
        if(m_lettresubstitution[nb] != '\0')
        {
            int nb2 = m_lettresubstitution[nb] - 'A';
            correspondancelettre[nb2] = nb;
        }
    }

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
        char lettre2 = correspondancelettre[lettre] + 'A';
        if( isspecial || (correspondancelettre[lettre] == 26) )
          textCode = textCode + mot[nb];
        else
          textCode = textCode + lettre2;
    }

    for(int nb89 = 0; nb89 < ((int)(textCode.length())); nb89++)
        textCode[nb89] = tolower(textCode[nb89]);

    textCode[0] = toupper(textCode[0]);

    for(int nb=2; nb < ((int)(textCode.length()) - 1); nb++)
    {
        if( (textCode[nb-1] == '.' || textCode[nb-1] == '?' || textCode[nb-1] == '!' ) || (textCode[nb - 1] == ' ' && (textCode[nb-2] == '.' || textCode[nb-2] == '?' || textCode[nb-2] == '!')) )
            textCode[nb] = toupper(textCode[nb]);
    }

    return textCode;
}
*/


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

bool estPrems(unsigned long long int nb)
{
    if(nb <= 1)
        return false;
    for (int nb2 = 2; nb2 <= (int)(sqrt(nb)); nb2 ++)
       if (nb % nb2 == 0)
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
