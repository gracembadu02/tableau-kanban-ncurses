
# Conventions de code Tableau de type kanban 


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



### Variables locales contenues dans les fonctions
+ **Convention** : camelCase
+ **Exemples** :
  + `isSelected`



### Constantes
+ **Convention** : SCREAMING_SNAKE_CASE
+ **Exemples** :
  + `COL_DEFAULT = 1`


### Membres privés de la classe
+ **Convention** : Préfixe m_ and camelCase
+ **Exemples** :
  + `m_id`



### Variables = Rôle, des variables qui servent de paramètres dans les fonctions
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



### Collections
+ **Convention** : Avec type and camelCase
+ **Exemples** :
  + `listeTaches`



### largeurs maximum de ligne
+ **Convention** : 200 caractères  



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
