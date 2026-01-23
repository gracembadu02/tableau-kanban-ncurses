#pragma once

#include <string>
#include <memory>

class Tache 
{
    public:
        int identifiant;
        std::string titre;
        std::string description;
        int priorite;

    Tache(int identifiant, std::string titre, std::string description, int priorite)
    {    
        this->identifiant= identifiant; 
        this->titre= titre; 
        this->description= description; 
        this->priorite= priorite;
    }
    
    std::string get_titre()
    {
        return titre;
    }

    std::string get_description()
    {
        return description;
    }

    int get_priorite()
    {
        return priorite;
    }
    
    void set_priorite(int priorite)
    {
        this->priorite =priorite; 
    }

};
// Alias pour un pointeur partagé vers une tâche
using tache_ptr = std::shared_ptr<Tache>;

