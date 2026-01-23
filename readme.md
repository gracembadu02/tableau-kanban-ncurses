
# Gestion d'un tableau du type kanban en ligne de commande 

## Description générale du système

Projet1, développé en **C++**, est une application de gestion de tâches de type Kanban exécutée dans le terminal.

Le système permet à un utilisateur de visualiser, créer, modifier, supprimer et déplacer des tâches entre **trois (3) colonnes**. 
Il permet aussi de gérer des priorités visuelles tout en renonçant à une interface utilisateur traditionnelle.

L'application de base suit un modèle simple à **trois (3) colonnes fixes** :
- TODO
- EN COURS
- TERMINÉ

## Exigences et spécifications

### Contraintes techniques
Le projet comprend les contraintes suivantes :
- Langage : C++ (C++17 recommandé)
- Bibliothèque obligatoire : ncurses
- Environnement : terminal
- Interface : clavier uniquement
- Résolution minimale du terminal : 60x20
- Nombre de colonnes : fixe (3)


## Scénarios utilisateur
En tant qu'utilisateur, je veux :
- naviguer entre les colonnes afin de voir l'état de mes tâches ;
- créer une tâche avec un titre, une description et une priorité afin de planifier mon travail ;
- modifier une tâche existante afin de corriger ou mettre à jour son contenu ;
- déplacer une tâche pour indiquer son avancement ;
- supprimer une tâche afin de garder un tableau clair.


## Structure du projet
```
projet/
├── src/
│   ├── main.cpp
│   ├── Tableau.cpp
│   ├── Tableau.h
│   ├── Colonne.h
│   └── Tache.h
├── readme.md
└── conventions.md
```


## Guide utilisateur

###  Description succincte du projet
L'application est un gestionnaire de tâches Kanban en mode texte, développé pour une utilisation rapide, efficace et intuitive.

### Démarrage
1. Assurez-vous d'avoir tous les prérequis
2. Compilez le programme
3. Exécutez le programme

Si vous n'êtes pas sûr comment procéder, dirigez-vous à la section **Installation et déploiement**

### Commandes clavier
| Touche        | Action                           |
| ------------- | -------------------------------- |
| ← / →         | Changer de colonne               |
| ↑ / ↓         | Naviguer entre les tâches        |
| **N**         | Nouvelle tâche                   |
| **E / M**     | Modifier la tâche sélectionnée   |
| **Entrée**    | Déplacer la tâche vers la droite |
| **Backspace** | Déplacer la tâche vers la gauche |
| **D**         | Supprimer la tâche               |
| **Q**         | Quitter l’application            |

### Procédure pas à pas pour la création et la modification d'une nouvelle tâche

1. Appuyer sur **N**
2. Entrer le titre, la description et la priorité de la nouvelle tâche
3. Naviguer jusqu'à la tâche avec les flèches de navigation
4. Appuyer sur **Entrée** pour la déplacer
5. Modifier la tâche avec **E**
6. Quitter l'application avec **Q**

###Déplacer vers la gauche (TERMINE -> EN COURS-> TODO)**

1. Dans la colonne `EN COURS` ou `TERMINE`, déplace le symbole `>` devant une tâche quelconque 
2. Appuie sur la touche `BACKSPACE` du clavier 
3. La tâche se déplace vers la gauche 


## Problèmes fréquents et solutions
- Le programme quitte immédiatement:
	-  Vérifier la taille du terminal
- Les couleurs ne s'affichent pas:
	- Vérifier le support des couleurs du terminal
- Erreur de compilation:
	- Vérifier que ncurses est installé
- Clavier non reconnu:
	- Lancer dans un vrai terminal (pas IDE intégré)


## Installation et déploiement

### Prérequis
- Linux ou macOS
- g++ (compilateur C++)
- ncurses (bibliothèque d'interface terminal)

### Étapes d'installation

**Sur Ubuntu/Debian :**
1. Compilateur g++

```bash
sudo apt install g++
```

2. Bibliothèque ncurses
 
```bash
sudo apt install libncurses5-dev libncursesw5-dev
```

**Sur macOS :**
```bash
brew install ncurses
```

### Compilation du programme
```bash
g++ Tableau.cpp main.cpp -lncurses 
```

### Exécution du programme
```bash
./a.out
```

Aucune configuration externe n’est requise

## Stratégie de test
Afin de tester l'interface, vous pouvez réaliser plusieurs types de tests :
- Tests manuels interactifs
- Tests fonctionnels par scénario utilisateur
- Tests de robustesse (entrées invalides, dimensions du terminal, etc.)  

### Cas de test fonctionnels
Vous pouvez tester la fonctionnalité en :
- Créant une tâche avec une priorité invalide 
- Déplaçant une tâche vide
- Naviguant dans une colonne vide
- Modifiant partiellement une tâche

### Tests de non-régression
Quelques tests de non-régression permettent de vérifier :
- Navigation après suppression
- Défilement après déplacement
- Priorités après modification

### Résultats et rapports
Vous pouvez considérer les tests comme réussis si :
- Aucun crash n’est constaté dans les scénarios normaux 
- La gestion des erreurs via exceptions est correcte
- Le code est structuré et modulaire

### Tests de performance
Vous pouvez tester la performance en vérifiant :
- La fluidité de l'interface jusqu'à plusieurs dizaines de tâches
- L’efficacité du défilement vertical


## Personnalisation des couleurs du terminal

Si vous souhaitez personnaliser votre terminal, vous pouvez le faire.  
Les couleurs utilisées par l'application sont définies via **ncurses** dans `Tableau::initialiser_ncurses()`.

Afin de les modifier, dirigez-vous dans le fichier `Tableau.cpp` et modifiez les appels suivants:

```cpp
init_pair(COULEUR_SELECTIONNEE, COLOR_BLACK, COLOR_CYAN);
init_pair(COULEUR_TITRE, COLOR_YELLOW, -1);
init_pair(COULEUR_ELEVEE, COLOR_RED, -1);
init_pair(COULEUR_MILIEU, COLOR_YELLOW, -1);
init_pair(COULEUR_BASSE, COLOR_GREEN, -1);
```

avec les couleurs disponibles de votre choix:
- `COLOR_BLACK`
- `COLOR_RED`
- `COLOR_GREEN`
- `COLOR_YELLOW`
- `COLOR_BLUE`
- `COLOR_MAGENTA`
- `COLOR_CYAN`
- `COLOR_WHITE`





