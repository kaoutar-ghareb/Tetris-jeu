# Tetris en C (SDL3)

Bienvenue dans mon projet Tetris ! Ce jeu a été développé en **langage C** en utilisant la bibliothèque graphique **SDL3**. C'est un projet réalisé dans le cadre de mes études à l'**ISI** pour mettre en pratique les concepts de programmation structurée et de gestion d'interfaces graphiques.

## Fonctionnalités
- **Deux modes de difficulté** : Facile (vitesse normale) et Difficile (vitesse accélérée + score doublé).
- **Système de score** et gestion des niveaux.
- **Aperçu de la pièce suivante**.
- **Interface rétro** avec une police de caractères personnalisée en pixels.

## Structure du Projet
Le projet est organisé de manière modulaire :
- `tetris.h` : Contient les définitions des structures, les constantes et les prototypes des fonctions.
- `main.c` : Contient la logique du jeu, la boucle principale et la gestion de l'affichage.

## Comment jouer 
1. **Prérequis** : Un compilateur C (MinGW recommandé).
2. **Bibliothèque** : Téléchargez les binaires de la **SDL3** pour Windows.
3. **Compilation** (via Terminal) : 
   Remplacez les chemins vers vos dossiers SDL3 :
   ```bash
   gcc main.c -o tetris.exe -I"C:/chemin/vers/SDL3/include" -L"C:/chemin/vers/SDL3/lib" -lSDL3
4. **Note cruciale** : Copiez le fichier `SDL3.dll` (présent dans le dossier `bin` de la bibliothèque SDL3) dans le même dossier que votre `tetris.exe` avant de lancer le jeu.

### Pourquoi c'est important ?
Sur Windows, un programme `.exe` a besoin de ses "dépendances" (les fichiers `.dll`) pour fonctionner. En incluant cette étape, on s'assure que le lien entre le code et la bibliothèque graphique est correctement établi lors de l'exécution.
   
