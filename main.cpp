#include <iostream>
#include <memory>
#include "Tableau.h"

int main()
{
    try 
    {   // Création d'un tableau Kanban unique et lancement de l'application
        auto tableau = std::make_unique<Tableau>();
        tableau->executer();
        return 0;
    } 
    catch(const exception& e) 
    {   
        // Gestion des exceptions standard : affichage du message d'erreur
        std::cerr << "ERREUR : " << e.what() << std::endl;
        return 1;
    } 
    catch(...) 
    {  
        // Gestion des exceptions inconnues : code d'erreur générique
        std::cerr << "ERREUR : code inconnu (E999)" << std::endl;
        return 2;
    }
}
