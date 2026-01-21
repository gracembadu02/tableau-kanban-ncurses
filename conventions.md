
# Conventions de code Tableau de type kanban 
**IGL 201 : Exercice 1**

Université de Sherbooke 


## Langage de programation
C++

## Langue utilisée :
Français 

## Nommage 

### Classes et Types 
+ **Convention** : PascalCase 
+ **Exemples** :
  + `class Tableau` ou `class MonTableau`
  + `enum CouleurT`


### Fonctions 
+ **Convention** : snake_case
+ **Exemples** :
  + `draw_column`



### Variables 
+ **Convention** : snake_case
+ **Exemples** :
  + `is_selected`



### Constantes
+ **Convention** : SCREAMING_SNAKE_CASE
+ **Exemples** :
  + `COL_DEFAULT = 1`



### Variables globales 
+ **Convention** : Préfixe g_ and  Pascalcase
+ **Exemple** :
  + ` g_compteurGlobal`



### Membres privés de la classe
+ **Convention** : Préfixe m_ and camelCase
+ **Exemples** :
  + `m_id`




### Variable = Rôle 
+ **Convention** : snake_case
+ **Exemples** :
  + `Tache tache_selectionnee`



### Relation portée/ longueur du nom 
+ **Convention** : Nom long et descriptif
+ **Exemples** : 
  + `getPriorite`

+ **Convention** : Temporaire 
+ **Exemples**:
  + `i`



### Accesseurs / mutateurs 
+ **Convention** : get/set and snake_case
+ **Exemples** :
  + `get_prio`



### Méthodes de calcul
+ **Convention** : Contextualisé and camelCase
+ **Exemples** :
  + `drawColumn()`




### Collections
+ **Convention** : Avec type and camelCase
+ **Exemples** :
  + `listeTaches`




### largeurs maximum de ligne
+ **Convention** : 80 caractère par ligne 


### Styles de blocs 
+ **Convention** : Accolade ouvrante sur une nouvelle ligne 
+ **Exemples** :
```cpp

void Tableau::move_left() 
{
    try 
    {
        current_col--;
        if(current_col < 0) current_col = num_cols - 1;
        current_task = 0;
        scroll_offsets[current_col] = 0;
    } catch(...) 
    {
        throw runtime_error("E200");
    }
}
```



### Indentations  
+ **Convention** : 4 espaces 
+ **Exemples** :
```cpp

void Tableau::move_left() 
{
    try
    {
        current_col--;
        if(current_col < 0) current_col = num_cols - 1;
        current_task = 0;
        scroll_offsets[current_col] = 0;
    } catch(...) 
    {
        throw runtime_error("E200");
    }
}
```



### Une seule ligne pour séparer les fonctions
+ **Exemples** :
```cpp

void Tableau::move_left() 
{

    current_col--;
    if(current_col < 0) current_col = num_cols - 1;
    current_task = 0;
    scroll_offsets[current_col] = 0;
}

void Tableau::afficher()
{
    cout << "coul";   
        
}
```


### Commentaires  
+ Commenter les algorithmes complexes
