#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>

#include "Tableau.h"

Tableau::Tableau() 
    : m_colonneCourante(0), m_tacheCourante(0), 
      m_identifiantSuivant(1), m_numeroColonnes(3)
{
    try 
    {    //Vérifie que le nombre de colonnes est valide
        if( m_numeroColonnes <= 0) throw runtime_error("E100 : nombre de colonnes invalide");
    } 
    catch(const runtime_error& e) 
    {
        throw;
    }
}

Tableau::~Tableau() 
{
    try 
    {
        nettoyer();
    } 
    catch(...) 
    {
         // Ignorer les erreurs lors du nettoyer
    }
}

void Tableau::initialiser_ncurses() 
{
    try
    {   // Initialise l'écran ncurses
        if(!initscr()) throw runtime_error("E101");
        
        // Configure les différentes erreurs et mode de saise 
        if(!initscr()) throw std::runtime_error("E101 : échec de l'initialisation ncurses");
        if(cbreak() == ERR) throw std::runtime_error("E102 : impossible de passer en mode cbreak");
        if(noecho() == ERR) throw std::runtime_error("E103 : impossible de désactiver echo");
        if(keypad(stdscr, TRUE) == ERR) throw std::runtime_error("E104 : impossible d'activer les touches spéciales");
        curs_set(0);
        
        // Initialise le système de couleurs 
        if(!has_colors()) throw std::runtime_error("E105 : couleurs non supportées");
        if(start_color() == ERR) throw std::runtime_error("E106 : impossible d'initialiser les couleurs");
        use_default_colors();
        
        // Spécifie les paires de couleurs pour l'interface
        init_pair(COULEUR_DEFAULT, COLOR_WHITE, -1);
        init_pair(COULEUR_SELECTIONNEE, COLOR_BLACK, COLOR_CYAN);
        init_pair(COULEUR_TITRE, COLOR_YELLOW, -1);
        init_pair(COULEUR_ELEVEE, COLOR_RED, -1);
        init_pair(COULEUR_MILIEU, COLOR_YELLOW, -1);
        init_pair(COULEUR_BASSE, COLOR_GREEN, -1);
        
        // Vérifie si la taille du terminal est suffisante
        getmaxyx(stdscr, m_hauteur, m_largeur);
        if(m_largeur < 60 || m_hauteur < 20) throw runtime_error("E107  : taille du terminal trop petite");
    } 
    catch(const runtime_error& e) 
    {
        endwin();
        throw;
    }
}

void Tableau::configurer_colonnes() 
{
    try 
    {  
        // Crée les trois colonnes du tableau kanban
        m_listeColonnes.push_back(make_unique<Colonne>("TODO"));
        m_listeColonnes.push_back(make_unique<Colonne>("EN COURS"));
        m_listeColonnes.push_back(make_unique<Colonne>("TERMINE"));
        
        m_decalagesDefilement.resize(m_numeroColonnes, 0);
        
        m_listeColonnes[0]->ajouter_tache(make_shared<Tache>(m_identifiantSuivant++, "Documentation", 
                          "Faire le fichier readme.md de ce programme", 1));
        m_listeColonnes[0]->ajouter_tache(make_shared<Tache>(m_identifiantSuivant++, "Convention", 
                          "Conventionner ce code", 2));
        m_listeColonnes[0]->ajouter_tache(make_shared<Tache>(m_identifiantSuivant++, "Documentation 2", 
                          "Mettre des commentaires lorsque nécessaire", 2));
        m_listeColonnes[2]->ajouter_tache(make_shared<Tache>(m_identifiantSuivant++, "Exécuter ce programme", 
                          "g++ Tableau.cpp main.cpp -lncurses", 3));
    } 
    catch(const exception& e) 
    {
        throw runtime_error("E108");
    }
}

void Tableau::creer_fenetres() 
{
    try 
    {   
        // Calcule les mesures de chaque colonne
        m_largeurColonne = m_largeur / m_numeroColonnes;
        m_hauteurColonne = m_hauteur - 3;
        
        // Vérifie si les mesures sont valides 
        if(m_largeurColonne < 20 || m_hauteurColonne < 10) 
            throw runtime_error("E109");
        
        m_colonnesFenetres.clear();

        // Crée une fenetre ncurses pour chaque colonne
        for(int i = 0; i < m_numeroColonnes; i++) 
        {   
            // Calcule les dimensions de la fenetre
            WINDOW* nouvelleFenetre = newwin(m_hauteurColonne, m_largeurColonne, 2, i * m_largeurColonne);
            if(!nouvelleFenetre) 
                throw runtime_error("E110  : impossible de créer la fenêtre");
            m_colonnesFenetres.emplace_back(nouvelleFenetre, delwin);
        }
    } 
    catch(const runtime_error& e) 
    {
        throw;
    }
}

void Tableau::dessiner() 
{
    try 
    {
        clear();
        
        // Affiche le titre principal
        attron(COLOR_PAIR(COULEUR_TITRE) | A_BOLD);
        mvprintw(0, m_largeur/2 - 10, "TABLEAU DE TYPE KANBAN");
        attroff(COLOR_PAIR(COULEUR_TITRE) | A_BOLD);
        
        // Affiche l'aide
        mvprintw(m_hauteur-1, 2, "TODO: commandes");
        
        refresh();
        
        for(int i = 0; i < m_numeroColonnes; i++) 
        {
            dessiner_colonne(i);
        }
    } 
    catch(const exception& e) 
    {
        throw runtime_error("E111 : erreur lors du dessin du tableau");
    }
}

void Tableau::dessiner_colonne(int index_colonne) 
{
    try 
    {   
        // Verifie que l'index de la colonne est valide
        if(index_colonne < 0 || index_colonne >= m_numeroColonnes) 
            throw runtime_error("E112 : indice de colonne invalide");
        
        WINDOW* fenetre = m_colonnesFenetres[index_colonne].get();
        werase(fenetre);
        
        // Affiche une bordure de couleur différente si la colonne est selectionnée
        if(index_colonne == m_colonneCourante) 
        {
            wattron(fenetre, COLOR_PAIR(COULEUR_SELECTIONNEE));
            box(fenetre, 0, 0);
            wattroff(fenetre, COLOR_PAIR(COULEUR_SELECTIONNEE));
        } 
        else 
        {
            box(fenetre, 0, 0);
        }
        
        wattron(fenetre, COLOR_PAIR(COULEUR_TITRE) | A_BOLD);
        mvwprintw(fenetre, 0, 2, " %s (%d) ", 
                  m_listeColonnes[index_colonne]->get_nom().c_str(), 
                  m_listeColonnes[index_colonne]->taille());
        wattroff(fenetre, COLOR_PAIR(COULEUR_TITRE | A_BOLD));
        
        //Calcule le nombre de tâche a afficher 
        int maxVisible = (m_hauteurColonne - 4) / 4;
        int debutIndex = m_decalagesDefilement[index_colonne];
        int finIndex  = min(debutIndex + maxVisible, m_listeColonnes[index_colonne]->taille());
        
        int y = 2;
        
        for(int i = debutIndex; i < finIndex; i++) 
        {
            bool isSelected = (index_colonne == m_colonneCourante && i == m_tacheCourante);
            dessiner_une_tache(fenetre, 
                               m_listeColonnes[index_colonne]->get_tache(i), 
                               isSelected, y);
            y += 4;
        }
        
        if(debutIndex > 0) 
        {
            mvwprintw(fenetre, 1, m_largeurColonne - 3, "+"); // en haut
        }
        
        
        if(finIndex < m_listeColonnes[index_colonne]->taille()) 
        {
            mvwprintw(fenetre, m_hauteurColonne - 2, m_largeurColonne - 3, "-"); // en bas
        }
        
        wrefresh(fenetre);
    } 
    catch(const exception& e) 
    {
        throw runtime_error("E113 : erreur lors du dessin d'une colonne");
    }
}

void Tableau::dessiner_une_tache(WINDOW* fenetre, tache_ptr tache, bool selectionne_tache, int position_y) 
{
    try 
    {  
        // Verifie que les parametres sont valides
        if(!tache) throw std::runtime_error("E114 : tâche nulle");
        if(!fenetre) throw std::runtime_error("E115 : fenêtre nulle");
        
        if(selectionne_tache) 
        {
            wattron(fenetre, COLOR_PAIR(COULEUR_SELECTIONNEE) | A_BOLD);
            mvwprintw(fenetre, position_y, 1, ">"); // sélectionné
        } 
        else 
        {
            mvwprintw(fenetre, position_y, 1, " ");
        }
        
        // Détermine la couleur selon la priorite
        int couleurPriorite = COULEUR_BASSE;
        if(tache->priorite == 1) 
            couleurPriorite = COULEUR_ELEVEE;

        else if(tache->priorite == 2) 
            couleurPriorite = COULEUR_MILIEU;
        
        // Affiche la priorite avec la couleur correspondante
        wattron(fenetre, COLOR_PAIR(couleurPriorite));
        mvwprintw(fenetre, position_y, 2, "[P%d]", tache->priorite);
        wattroff(fenetre, COLOR_PAIR(couleurPriorite));
        
        //Limiter la longueur de la description
        string titre = tache->titre;
        if(static_cast<int>(titre.length()) > m_largeurColonne - 10) 
        {
            titre = titre.substr(0, m_largeurColonne - 13) + "...";
        }
        mvwprintw(fenetre, position_y, 7, "%s", titre.c_str());
        
        // Affiche la description
        string descriptionTache = tache->description;
        if(static_cast<int>(descriptionTache.length()) > m_largeurColonne - 6) 
        {
            descriptionTache = descriptionTache.substr(0, m_largeurColonne - 9) + "...";
        }
        mvwprintw(fenetre, position_y+1, 2, "%s", descriptionTache.c_str());
        
        if(selectionne_tache) 
        {
            wattroff(fenetre, COLOR_PAIR(COULEUR_SELECTIONNEE) | A_BOLD);
        }
        
        // Trace une ligne de seperation
        mvwhline(fenetre, position_y+2, 1, ACS_HLINE, m_largeurColonne - 2);
    } 
    catch(const exception& e) 
    {
        throw runtime_error("E116 : erreur lors du dessin d'une tâche");
    }
}

// Boucle principale qui gère les entrées de l'utilisateur
void Tableau::executer() 
{
    try 
    {
        initialiser_ncurses();
        configurer_colonnes();
        creer_fenetres();
        
        bool enCours = true;
        
        while(enCours) 
        {
            try 
            {
                dessiner();
                
                int ch = getch(); // Attend une saisie du clavier
                
                switch(ch) 
                {
                    case 'q':
                    case 'Q':
                            enCours = false;
                        break;
                        
                    case KEY_LEFT:
                        aller_a_gauche();
                        break;
                        
                    case KEY_RIGHT:
                        aller_a_droite();
                        break;
                        
                    case KEY_UP:
                        aller_vers_haut();
                        break;
                        
                    case KEY_DOWN:
                        aller_vers_bas();
                        break;
                    case 'n':
                    case 'N':
                        nouvelle_tache();
                        break;
                        
                    case 'e':
                    case 'E':
                    case 'm':
                    case 'M':
                        modifier_tache_actuelle();
                        break;
                        
                    case 10:
                        deplacer_tache_droite();
                        break;
                        
                    case KEY_BACKSPACE:
                    case 127:
                         deplacer_tache_gauche();
                        break;
                        
                    case 'd':
                    case 'D':
                        supprimer_tache();
                        break;
                }
            } 
            catch(const exception& e) 
            {

            }
        }
        
        nettoyer();
    } 
    catch(const exception& e) 
    {
        nettoyer();
        throw;
    }
}

void Tableau::aller_a_gauche() 
{
    try 
    {
        m_colonneCourante--;
        if(m_colonneCourante < 0) m_colonneCourante = m_numeroColonnes - 1;
        m_tacheCourante= 0;
        m_decalagesDefilement[m_colonneCourante] = 0;
    } 
    catch(...) 
    {
        throw runtime_error("E200 : erreur navigation colonne gauche");
    }
}

void Tableau::aller_a_droite() 
{
    try 
    {
        m_colonneCourante++;
        if(m_colonneCourante >= m_numeroColonnes) m_colonneCourante = 0;
        m_tacheCourante = 0;
        m_decalagesDefilement[m_colonneCourante] = 0;
    } 
    catch(...) 
    {
        throw runtime_error("E201 : erreur navigation colonne droite");
    }
}

void Tableau::aller_vers_haut() 
{
    try 
    {
        m_tacheCourante--;

        if(m_tacheCourante < 0) 
        {
            m_tacheCourante = m_listeColonnes[m_colonneCourante]->taille() - 1;
        }
        if(m_tacheCourante < 0) m_tacheCourante = 0;
        
        if(m_tacheCourante < m_decalagesDefilement[m_colonneCourante])
        {
            m_decalagesDefilement[m_colonneCourante] = m_tacheCourante;
        }
    } 
    catch(...) 
    {
        throw runtime_error("E202 : erreur navigation tache haut");
    }
}

void Tableau::aller_vers_bas() 
{
    try 
    {
        m_tacheCourante++;
        if(m_tacheCourante >= m_listeColonnes[m_colonneCourante]->taille()) 
        {
            m_tacheCourante = 0;
        }
        
        int maxVisible = (m_hauteurColonne - 4) / 4;
        
        // Modifie le defilement si la tache depasse le cadre 
        if(m_tacheCourante >= m_decalagesDefilement[m_colonneCourante] + maxVisible) 
        {
            m_decalagesDefilement[m_colonneCourante] = m_tacheCourante - maxVisible + 1;
        }
    } 
    catch(...) 
    {
        throw runtime_error("E203: erreur navigation tache bas");
    }
}

void Tableau::nouvelle_tache() 
{
    try 
    {
        echo(); // affichage des caractères 
        curs_set(1); // affiche le curseur
        
        WINDOW* fenetreEntree = newwin(10, 60, m_hauteur/2 - 5, m_largeur/2 - 30);
        if(!fenetreEntree) throw runtime_error("E300  : impossible de créer la fenêtre d'entrée");
        
        unique_ptr<WINDOW, decltype(&delwin)> win_guard(fenetreEntree, delwin);
        
        box(fenetreEntree, 0, 0);
        
        // Affiche les libéles associés pour chaque champ
        mvwprintw(fenetreEntree, 2, 2, "Titre:");
        mvwprintw(fenetreEntree, 4, 2, "Description:");
        mvwprintw(fenetreEntree, 6, 2, "Priorité (1-3):");
        
        wrefresh(fenetreEntree);
        
        char titre[50];
        char description[50];
        int priorite;
        
        // Récupère les informations de l'utilisateur 
        mvwgetnstr(fenetreEntree, 2, 10, titre, 45);
        mvwgetnstr(fenetreEntree, 4, 16, description, 40);
        mvwscanw(fenetreEntree, 6, 19, "%d", &priorite);
        
        if(priorite < 1) priorite = 1;
        if(priorite > 3) priorite = 3;
        
        auto tache = make_shared<Tache>(m_identifiantSuivant++, string(titre), string(description), priorite);
        m_listeColonnes[0]->ajouter_tache(tache);
        
        noecho();
        curs_set(0);
    } 
    catch(const exception& e) 
    {
        noecho();
        curs_set(0);
        throw runtime_error("E301 : erreur lors de la création d'une tâche");
    }
}


void Tableau::modifier_tache_actuelle() 
{
    try 
    {   
        // Vérifie que la colonne contient au moins une tâche
        if(m_listeColonnes[m_colonneCourante]->taille() == 0) return;
      
        auto tache = m_listeColonnes[m_colonneCourante]->get_tache(m_tacheCourante);
        if(!tache) throw runtime_error("E600 : tâche nulle");
      
        echo();
        curs_set(1);
         
        WINDOW* modifieFenetre = newwin(14, 70, m_hauteur/2 - 7,  m_largeur/2 - 35);
        if(!modifieFenetre) throw runtime_error("E601 : impossible de créer la fenêtre d'édition");
      
        unique_ptr<WINDOW, decltype(&delwin)> win_guard(modifieFenetre, delwin);
      
        box(modifieFenetre, 0, 0);
        
        //Affiche les valeurs actuelles de la tâche 
        mvwprintw(modifieFenetre, 2, 2, "Actuel:");
        wattron(modifieFenetre, COLOR_PAIR(COULEUR_DEFAULT));
        mvwprintw(modifieFenetre, 3, 4, "Titre: %s", tache->titre.c_str());
        mvwprintw(modifieFenetre, 4, 4, "Desc:  %s", tache->description.c_str());
        mvwprintw(modifieFenetre, 5, 4, "Prio:  %d", tache->priorite);
        wattroff(modifieFenetre, COLOR_PAIR(COULEUR_DEFAULT));
      
        
        mvwprintw(modifieFenetre, 7, 2, "Nouveau (vide = conserver):");
        mvwprintw(modifieFenetre, 8, 2, "Titre:");
        mvwprintw(modifieFenetre, 9, 2, "Desc:");
        mvwprintw(modifieFenetre, 10, 2, "Prio:");
      
        wrefresh(modifieFenetre);
      
        char titre[50] = {0};
        char description[50] = {0};
        char chainePriorite[10] = {0};
      
        mvwgetnstr(modifieFenetre, 8, 9, titre, 45);
        mvwgetnstr(modifieFenetre, 9, 9, description, 45);
        mvwgetnstr(modifieFenetre, 10, 9, chainePriorite, 5);
      
        if(strlen(titre) > 0) 
        {
            tache->titre = string(titre);
        }
        
        if(strlen(description) > 0) 
        {
            tache->description = string(description);
        }
        
        if(strlen(chainePriorite) > 0) 
        {
            int nouvellePriorite = atoi(chainePriorite);
            if(nouvellePriorite  < 1) nouvellePriorite = 1;
            if(nouvellePriorite  > 3) nouvellePriorite = 3;
            tache->priorite = nouvellePriorite ;
        }
      
      noecho();
      curs_set(0);
    } 
    catch(const exception& e) 
    {
      noecho();
      curs_set(0);
      throw runtime_error("E602  : erreur lors de la modification d'une tâche");
    }
}


void Tableau::deplacer_tache_droite() 
{
    try 
    {   
        // Vérifie que nous ne sommes pas dans la derniére colonne
        if(m_colonneCourante >= m_numeroColonnes - 1) return;
        if(m_listeColonnes[m_colonneCourante]->taille() == 0) return;
        
        //Déplace la tâche vers la colonne de droite
        auto tache = m_listeColonnes[m_colonneCourante]->get_tache(m_tacheCourante);
        m_listeColonnes[m_colonneCourante + 1]->ajouter_tache(tache);
        m_listeColonnes[m_colonneCourante]->supprimer_tache(m_tacheCourante);
        
        if(m_tacheCourante >= m_listeColonnes[m_colonneCourante]->taille()) 
        {
            m_tacheCourante = m_listeColonnes[m_colonneCourante]->taille() - 1;
            if(m_tacheCourante < 0) m_tacheCourante = 0;
        }
        
        int maxVisible = (m_hauteurColonne - 4) / 4;

        if(m_decalagesDefilement[m_colonneCourante] > 0 && 
           m_listeColonnes[m_colonneCourante]->taille() <= m_decalagesDefilement[m_colonneCourante] + maxVisible) 
        {
            m_decalagesDefilement[m_colonneCourante] = max(0, m_listeColonnes[m_colonneCourante]->taille() - maxVisible);
        }
    } 
    catch(const exception& e) 
    {
        throw runtime_error("E400 : erreur déplacement tâche droite");
    }
}


void Tableau::deplacer_tache_gauche() 
{
    try 
    {   
        // Vérifie que nous sommes dans la colonne TODO
        if(m_colonneCourante <= 0) return;
        if(m_listeColonnes[m_colonneCourante]->taille() == 0) return;
        
        //deplace la tâche vers la gauche
        auto tache = m_listeColonnes[m_colonneCourante]->get_tache(m_tacheCourante);
        m_listeColonnes[m_colonneCourante - 1]->ajouter_tache(tache);
        m_listeColonnes[m_colonneCourante]->supprimer_tache(m_tacheCourante);
        
        if(m_tacheCourante >= m_listeColonnes[m_colonneCourante]->taille()) 
        {
            m_tacheCourante = m_listeColonnes[m_colonneCourante]->taille() - 1;
            if(m_tacheCourante < 0) m_tacheCourante= 0;
        }
        
        int maxVisible = (m_hauteurColonne - 4) / 4;
        if(m_decalagesDefilement[m_colonneCourante] > 0 
            && m_listeColonnes[m_colonneCourante]->taille() <= 
            m_decalagesDefilement[m_colonneCourante] + maxVisible) 
        {
            m_decalagesDefilement[m_colonneCourante] = 
            max(0, m_listeColonnes[m_colonneCourante]->taille() - maxVisible);
        }
    } 
    catch(const exception& e) 
    {
        throw runtime_error("E401 : erreur déplacement tâche gauche");
    }
}


void Tableau::supprimer_tache() 
{
    try 
    {   
        // Vérifie qu'il existe  au moins une tache a supprimer
        if(m_listeColonnes[m_colonneCourante]->taille() == 0) return;
        
        m_listeColonnes[m_colonneCourante]->supprimer_tache(m_tacheCourante);
        
        // Régler la selection après suppression
        if(m_tacheCourante >= m_listeColonnes[m_colonneCourante]->taille()) 
        {
            m_tacheCourante = m_listeColonnes[m_colonneCourante]->taille() - 1;
            
            if(m_tacheCourante < 0) m_tacheCourante = 0;
        }
        
        // Régler le défilement si nécessaire
        int maxVisible = (m_hauteurColonne - 4) / 4;
        if(m_decalagesDefilement[m_colonneCourante] > 0 &&  
            m_listeColonnes[m_colonneCourante]->taille() <= 
            m_decalagesDefilement[m_colonneCourante] + maxVisible) 
        {
            m_decalagesDefilement[m_colonneCourante] = 
            max(0, m_listeColonnes[m_colonneCourante]->taille() - maxVisible);
        }
    } 
    catch(const exception& e) 
    {
        throw runtime_error("E500 : erreur suppression tâche");
    }
}

 
void Tableau::nettoyer() 
{
    try 
    {  
        m_colonnesFenetres.clear();
        m_listeColonnes.clear();
        endwin();//termine le mode ncurses
    } 
    catch(...) 
    {
         // Ignorer les erreurs pendant le nettoyer
    }
}
