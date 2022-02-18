#include "outils_big_int.h"

bool estprems_big(boost::multiprecision::cpp_int nb)
{
    if(nb <= 3)
        return nb > 1;
    if(nb % 2 == 0 || nb % 3 == 0)
        return false;
    boost::multiprecision::cpp_int sqrt_nb = boost::multiprecision::sqrt(nb);
    // Les nombres premiers sont de la forme 6k+1 ou 6k-1
    // Preuve :
    // Si n % 6 = 1, alors n peut être premier
    // Si n % 6 = 0, 2, 4, alors 2 | n
    // Si n % 6 = 3, alors 3 | n
    // Si n % 6 = 5 = -1, alors n peut être premier

    // on peut ne tester que les nombres premiers <= à sqrt_n
    // (on en teste même un peu plus mais bon...)
    for (boost::multiprecision::cpp_int i = 5; i <= sqrt_nb; i += 6)
       if (nb % i == 0 || nb % (i+2) == 0)
            return false;

    return true;
}

double index_of_coincidence_big(std::string text)
{
    text = garderLettres(supprimerAccents(text));
    boost::multiprecision::cpp_int l = text.length();

    std::vector<int> alphabet;
    analyse(text, alphabet);

    boost::multiprecision::cpp_int index_of_coincidence = 0;

    for(int i = 0; i < 26; i++)
    {
        index_of_coincidence += boost::multiprecision::cpp_int (alphabet[i] * (alphabet[i] - 1));

    }

    return double(index_of_coincidence) / double((l)*(l-1));
}