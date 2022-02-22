#include "../outils.h"

void help()
{
    std::cout << "Calculatrice par Edre2\n";
    std::cout << "\n";
    std::cout << "Entrez un calcul puis tapez sur Entrer\n";
    std::cout << "Expressions autorisées : +, -, −, *, ×, /, ÷, ^, (, )\n";
    std::cout << "Fonctions autorisées : sin, asin, cos, acos, tan, atan, sqrt, max, pgcd\n";
    std::cout << "\n";
    std::cout << "Pour quitter, entrez : q\n";
    std::cout << "Pour afficher l'aide, entrez : h\n";
    std::cout << "\n";
}

int main()
{
    help();

    std::string calcul = "";

    // Tant que l'utilisateur ne quitte pas, on lui propose de faire des calculs
    while(calcul != "q")
    {
        std::cout << ">> ";
        std::getline(std::cin, calcul);
        if(calcul == "h")
            help();
        else
         std::cout << "> " << calculer(calcul) << "\n";
    }

    return EXIT_SUCCESS;
}