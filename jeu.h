#ifndef JEU_H
#define JEU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAILLE_MIN_TABLEAU 6
#define TAILLE_MAX_TABLEAU 100
#define TAILLE_TORPILLEUR 2
#define TAILLE_CONTRE_TORPILLEUR 3
#define TAILLE_CROISEUR 4
#define TAILLE_PORTE_AVIONS 5

extern char dernier_navire_coule[20];

typedef enum {
   PORTE_AVIONS, CROISEUR, CONTRE_TORPILLEUR, TORPILLEUR
} TypeNavire;

typedef struct une_case {
   int x;
   int y;
} Case;

typedef struct navire {
   int sens;
   Case premiere_case;
   int taille;
   TypeNavire type;
   char nom[20];
} Navire;

typedef struct {
   TypeNavire type;
   int taille;
} InfoNavire;

void init_nb_aleatoire();

int nb_aleatoire(int max);

Navire creer_navire(int taille_plateau);

int est_valide(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau, Navire *navire);

void initialisation_plateau(Navire navires[], int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau);

void saisir_coordonnees(int *x, int *y);

int verifier_validite_coordonnees(int x, int y, int taille_plateau);

void verifier_navire_coule(int prop[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU],
                           Navire navires[], int num_bateau,
                           char dernier_navire_coule[]);

void proposition_joueur(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU],
                        int prop[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU],
                        int *nb_touche,
                        int *nb_joue,
                        int *nb_touche_nav,
                        Navire navires[],
                        int taille_plateau,
                        int *coups_deja_joues);

void affichage_entete(int taille_plateau);

void affichage_plateau(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau);

int saisir_taille_plateau();

void afficher_bateaux(Navire navires[], int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau);

int tous_bateaux_coules(int nb_touche_nav[], Navire navires[]);

#endif
