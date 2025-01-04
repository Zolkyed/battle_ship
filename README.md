# Bataille Navale en C

## Description
Ce programme écrit en langage C est une version du jeu de bataille navale. Il permet à l'utilisateur de jouer contre l'ordinateur en plaçant des navires sur une grille et en essayant de couler tous les navires ennemis en devinant leurs positions.

## Compilation
Pour compiler le programme, utilisez la commande suivante :
```
gcc -o bataille_navale main.c jeu.c statistiques.c
```

## Exécution
Pour exécuter le programme, utilisez la commande suivante :
```
./bataille_navale
```

Lorsque le logiciel est exécuté avec l'option -S, il accumulera les statistiques sur les données du jeu et écrira ces statistiques dans un fichier de sortie.

Exemple d'exécution du logiciel avec l'option -S :
```
bash> ./bataille_navale -S [Nom_Fichier_Sortie.txt]
```

| Paramètre                 | Description  |
|---------------------------|--------------|
| `-S`                      | Active le mode de statistiques |
| `[Nom_Fichier_Sortie.txt]` | Nom du fichier de sortie pour les statistiques |

## Prérequis
Commande pour installer les sous-modules Git
```
git submodule update --init
```

## Exécution des Tests

**L'exécution des tests se fait à partir du fichier tests**

test_jeu.c :
```c
gcc test_jeu.c ../jeu.c -o jeu_cunits  -lcunit 
```
test_statistiques.c :
```c
gcc test_statistiques.c ../jeu.c ../statistiques.c -o statistiques_cunits  -lcunit 
```
test bataille_navale.bats :
```c
bats bataille_navale.bats
```
Exécution:
```c
./jeu_cunits
./statistiques_cunits
./main_cunits
```

 ## Test

Exécutez le make dans la racine du projet :
```
make test
```

## Readme

Pour avoir le README.md sous format HTML, utilisez la commande suivante :
```
make html
```

## Auteur
Ce programme a été réalisé par Charles Hamelin.

