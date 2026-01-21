#fichier tache.h : Tache.h
**class tache** : class Tache 
**id** : identifiant
**titre** : titre
**desc** : description 
**priorite** : priorite

**GetTitle()** : get_titre  
**get_desc()** : get_description  
**getPrio()**  : get_priorite
**setprio(int p)** :set_priorite(int priorite)
**using tache_ptr = std::shared_ptr<tache>**



#fichier Column.h
**class Column** : class Column
**nom**: m_nom
**tasks** : m_listeTaches

**add_task(tache_ptr t)**: ajouter_tache(tache_ptr nouvelle_tache) 
**removeTask(int idx)** : supprimer_tache(int index)
**get_tache(int i )** : get_tache(int position) 
**size()** : taille_liste()
**getNom()** : get_nom()
**getTasks()** : get_listetaches()



#fichier Tableau.h

**enum couleur_t**: CouleurDesTaches
{
    **COL_DEFAULT**  = COULEUR_DEFAULT
    **COL_SELECTED** = COULEUR_SELECTIONNEE
    **COL_TITLE** = COULEUR_TITRE
    **COL_HIGH** = COULEUR_ELEVEE
    **COL_MED** = COULEUR_MILIEU
    **COL_LOW** = COULEUR_BASSE
}

**class Tableau** : class Tableau
**cols** : m_listeColonnes
**current_col**: m_colonneCourante
**current_task** : m_tacheCourante
**next_id** : m_identifiantSuivant
**col_windows** : m_colonnesFenetres
**num_cols** : m_numeroColonne
**scroll_offsets** : m_decalagesDefilement
**W** : m_largeur
**H** : m_hauteur
**col_w** : m_largeurColonne
**col_h** : m_hauteurColonne
    
**init_ncurses()** : initialiser_ncurses()
**setup_columns()** : configuer_colonnes()
**create_windows()** : creerUneFenetre()
**draw()** : dessiner()
**draw_column(int col_idx)** : dessine_colonne(int index_colonne)
        int max_visible = maxVisible
        int start_idx = debutIndex
        int end_idx =finIndex

**draw_task(WINDOW* win, tache_ptr t, bool selected, int y_pos)** : dessine_unetache(WINDOW fenetre, tache_ptr tache, bool selectionne, int position_y)
        int prio_color: couleurPriorite
        string title : titre
        string desc : descriptionTache

**run()** : courrir()
**move_left()** : aller_a_gauche()
**moveRight()** : aller_a_droite()
**move_up()** : aller_vers_haut()
**MoveDown()** : aller_vers_bas()
**nouvelle_tache()** : nouvelle_tache()
            WINDOW* input_win = fenetreEntree
            
**modifier_tache_actuelle()** : modifier_tache_actuelle()
         auto t  = auto tache
         WINDOW* edit_win = modifieFenetre
         char desc : description
         char prio_str[10] : chainePriorite
         int prio = nouvellePriorite 


**deplacer_tache_droite()** :  deplacer_tache_droite();
            auto t  = auto tache

**move_task_left()** : deplacer_tache_gauche()
           auto t  = auto tache

**supprimer_tache()** : supprimer_tache()
**cleanup()** : effacer()

