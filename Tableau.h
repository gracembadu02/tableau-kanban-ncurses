#pragma once

#include <ncurses.h>
#include <vector>
#include <memory>
#include "Colonne.h"
#include "Tache.h"

using namespace std;

// Couleurs utilisées pour l'affichage ncurses
enum CouleurDesTaches 
{
    COULEUR_DEFAULT = 1,
    COULEUR_SELECTIONNEE= 2,
    COULEUR_TITRE = 3,
    COULEUR_ELEVEE= 4,
    COULEUR_MILIEU= 5,
    COULEUR_BASSE= 6
};

class Tableau 
{
    private:
        vector<unique_ptr<Colonne>> m_listeColonnes;
        int m_colonneCourante;
        int m_tacheCourante;
        int m_identifiantSuivant;
        vector<unique_ptr<WINDOW, decltype(&delwin)>> m_colonnesFenetres;
        int m_numeroColonnes;
        vector<int> m_decalagesDefilement;
            
        int m_largeur, m_hauteur;
        int m_largeurColonne, m_hauteurColonne;
    
    public:
        Tableau();
        ~Tableau();

       //Initialise la bibliothèque ncurses pour l'affichage
        void initialiser_ncurses();

        // Configuration des colonnes et des tâches initiales
        void configurer_colonnes();
        void creer_fenetres();
    
        void dessiner();
        void dessiner_colonne(int index_colonne);
        void dessiner_une_tache(WINDOW* fenetre, tache_ptr tache, bool selectionne, int position_y);
    
        void executer();
        
        // Gestion des tâches
        void aller_a_gauche();
        void aller_a_droite();
        void aller_vers_haut();
        void aller_vers_bas();
        void nouvelle_tache();

        // Fonctions de navigation
        void modifier_tache_actuelle();
        void deplacer_tache_droite();
        void deplacer_tache_gauche();
        void supprimer_tache();
        
        // Nettoyage des ressources
        void nettoyer();
};
