#pragma once 

#include <vector>
#include <memory>
#include <stdexcept>
#include "Tache.h"

class Colonne
{
    private:
        std::string m_nom;
        std::vector<tache_ptr> m_listeTaches;

    public:
        Column(std::string nom)
        {
            if(nom.empty()) throw std::runtime_error("E001");
                m_nom = nom;
        }

        ~Column() = default;

        void ajouter_tache(tache_ptr nouvelle_tache) 
        { 
            //verifie si le pointeur de tâche est non null
            if (!nouvelle_tache) throw std::runtime_error("E002");
            m_listeTaches.push_back(nouvelle_tache);
        }

        bool supprimer_tache(int index) 
        {
            try
            {   // verifier si l'index de la tâche à supprimer est valide
                if (index < 0 || index>=static_cast<int>(m_listeTaches.size())) throw std::out_of_range("E003");
                m_listeTaches.erase(m_listeTaches.begin() + index);
                return true;
            }
            catch(const std::out_of_range& e) 
            {
            return false;
            }
        }

        tache_ptr get_tache(int position) 
        {   
            if(position < 0 || position >= static_cast<int>(m_listeTaches.size()))
                throw std::out_of_range("E004");
            return m_listeTaches[position];
        }

        int taille_liste() 
        { 
            return m_listeTaches.size(); 
        }

        std::string get_nom() 
        { 
            return m_nom; 
        }

        std::vector<tache_ptr>& get_listetaches() 
        { 
            return m_listeTaches; 
        }
};