
# Gestion d'un tableau du type kanban en ligne de commande 



## Description

Ce tableau a été conçu et développé avec la bibliothèque ncurses.
Il permet de gérer les tâches organisées en colonnes.

### Structure
Le tableau comporte 3 colonnes distinctes:

1. **TODO**, tâche à faire
2. **EN COURS**, tâche en cours 
3. **TERMINE**, tâche terminée 


### Composition d'une tâche 

1. Un identificateur unique(ID)
2. Un titre 
3. Une description
4. Une priorité 

### Priorité d'une tâche 
La priorité d'une tâche depend de sa couleur  

| Couleur |  Priorité  | Chiffre associé |
|---------|------------|-----------------|
| Rouge   |  Elevée    |     1           |
| Jaune   |  Moyenne   |     2           |
| Vert    |  Faible    |     3           |






## Installation et déploiement

### Prérequis

Avant de pouvoir compiler et exécuter ce programme, vous devez installer :
- Compilateur g++ du C++
- Bibliothèque ncurses 

### Étapes d'installation 

1. Compilateur g++

Dans le terminal tapez:
``` bash
sudo apt update  
```
ou 
```bash 
sudo apt install g++

```

2. Biblothèque ncurses 

Dans le terminal tapez:
``` bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```



## Utilisation


### Démarrage rapide

Le projet doit être exécuté sous le système d'exploitation Linux.Pour lancer le programme,utilisez le terminal. 
Voici à quoi ressemble le terminal: 
![Le terminal Linux](image.png)

Il existe  deux manières d'ouvrir le terminal dans le dossier du projet : 


#### Méthode 1 : Depuis le dossier du projet
1. Trouver l'emplacement du projet
2. Naviguez jusqu'au dossier contenant les fichiers `.h` et `.cpp `
3. Faites un clic droit dans le vide,une petite liste apparaît, cliquez sur **Ouvrir dans un terminal**

#### Méthode 2 : Depuis le terminal
1. Ouvrez le terminal(en utilisant la recherche d'application)
2. Naviguez vers le dossier du projet avec `cd`

Exemple: Si votre projet est dans Documents/projet  

```bash
cd Documents 
cd projet
```

#### Commande de compilation du programme

g++ Tableau.cpp main.cpp -lncurses




### Manuel utilisateur 

**Commandes**

| Commandes |        Description               |
|-----------|----------------------------------|
|`n` ou `N` |  Créer une nouvelle tâche        |
|`q` ou `Q` |  Quitter la fenêtre windows      |
|`e` ou `E` |  Modifier_tâche_actuelle         |
|`m` ou `M` |  Modifier_tâche_actuelle         |
|`d` ou `D` |  supprimer une tâche             |

**Changer de colonne**

Flèche droite `-­>`: Aller à la colonne de droite   
Flèche gauche `<-­`: Aller à la colonne de gauche  

**Naviguer entre les tâches**

Flèche haut : Aller vers la tâche précedente

Flèche bas : Aller vers la tâche suivante 


### Procédure pas-à-pas 
Chaque tâche crée, est mis dans la colonne `TODO`, précèdée du signe `>` 

**Déplacer vers la droite (TODO -> EN COURS-> TERMINE)**

1. Sélectionne une tâche dans TODO avec les flèches
2. Appuie sur `Entrée`
3. La tâche se déplace dans EN COURS

**Déplacer vers la gauche (TERMINE -> EN COURS-> TODO)**

1. Dans la colonne `EN COURS` ou `TERMINE`, déplace le symbole `>` devant une tâche quelconque 
2. Appuie sur la touche `BACKSPACE` du clavier 
3. La tâche se déplace vers la gauche 



### Solutions aux problèmes fréquents 

**Problèmes fréquents**: le programme ne compile pas 
**Cause** : Compilateur g++ et bibliothèque ncurses pas installé 

**Solution**: Installer les dépendances avec les commandes mentionnés dans la section `Installation`


### Messages d'aides et d'erreur clairs





Quel niveau de détail il attend dans chaque section?

Est-ce que certaines sections peuvent être omises si elles ne s'appliquent pas?

Est-ce que le readme.md doit couvrir tous les types de documentation ou juste certains?













