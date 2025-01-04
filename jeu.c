#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "jeu.h"

#define TAILLE_MIN_TABLEAU 6
#define TAILLE_MAX_TABLEAU 100
#define TAILLE_TORPILLEUR 2
#define TAILLE_CONTRE_TORPILLEUR 3
#define TAILLE_CROISEUR 4
#define TAILLE_PORTE_AVIONS 5

char dernier_navire_coule[20] = "";

InfoNavire infos_navires[] = {
        {PORTE_AVIONS,      TAILLE_PORTE_AVIONS},
        {CROISEUR,          TAILLE_CROISEUR},
        {CONTRE_TORPILLEUR, TAILLE_CONTRE_TORPILLEUR},
        {TORPILLEUR,        TAILLE_TORPILLEUR}
};

/**
 * Initialise le générateur de nombre aléatoire.
 *
 * Aucune valeur de retour.
 */
void init_nb_aleatoire() {
   srand(time(NULL));
}

/**
 * Génère un nombre aléatoire
 *
 * @param max La valeur maximale pour le nombre aléatoire
 * @return Un nombre aléatoire
 */
int nb_aleatoire(int max) {
   return (rand() % max);
}

/**
 * Crée un nouveau navire de façon aléatoire.
 *
 * @param taille_plateau La taille du plateau de jeu.
 * @return Un nouveau navire avec des caractéristiques aléatoires.
 */
Navire creer_navire(int taille_plateau) {
   Navire navire;
   int type_index = nb_aleatoire(4);

   navire.type = infos_navires[type_index].type;
   navire.taille = infos_navires[type_index].taille;

   switch (navire.type) {
      case PORTE_AVIONS:
         strcpy(navire.nom, "Porte-avions");
         break;
      case CROISEUR:
         strcpy(navire.nom, "Croiseur");
         break;
      case CONTRE_TORPILLEUR:
         strcpy(navire.nom, "Contre-torpilleur");
         break;
      case TORPILLEUR:
         strcpy(navire.nom, "Torpilleur");
         break;
   }

   navire.premiere_case.x = nb_aleatoire(taille_plateau);
   navire.premiere_case.y = nb_aleatoire(taille_plateau);
   navire.sens = nb_aleatoire(4);

   return navire;
}

/**
 * Vérifie si un navire peut être placé sur le plateau sans chevauchement et sans dépassement des limites.
 *
 * @param plateau Le plateau de jeu.
 * @param taille_plateau La taille du plateau de jeu.
 * @param navire Le navire à vérifier.
 * @return 1 si le navire peut être placé sur le plateau, sinon 0.
 */
int est_valide(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau, Navire *navire) {
   int x = navire->premiere_case.x;
   int y = navire->premiere_case.y;

   if (x < 0 || x >= taille_plateau || y < 0 || y >= taille_plateau)
      return 0;

   for (int i = 0; i < navire->taille; i++) {
      int nouveau_x = x;
      int nouveau_y = y;
      switch (navire->sens) {
         case 0:
            nouveau_x -= i;
            break;
         case 1:
            nouveau_y += i;
            break;
         case 2:
            nouveau_x += i;
            break;
         case 3:
            nouveau_y -= i;
            break;
      }

      if (nouveau_x < 0 || nouveau_x >= taille_plateau || nouveau_y < 0 || nouveau_y >= taille_plateau ||
          plateau[nouveau_x][nouveau_y] != 0)
         return 0;
   }
   return 1;
}

/**
 * Initialise le plateau de jeu en plaçant 5 navires de manière aléatoire.
 *
 * @param navires Un tableau de navires à initialiser.
 * @param plateau Le plateau de jeu.
 * @param taille_plateau La taille du plateau de jeu.
 */
void initialisation_plateau(Navire navires[], int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau) {
   int num_bateau = 1;

   for (int i = 0; i < 5; i++) {
      Navire navire = creer_navire(taille_plateau);

      while (!est_valide(plateau, taille_plateau, &navire)) {
         navire = creer_navire(taille_plateau);
      }

      navires[i] = navire;

      for (int j = 0; j < navire.taille; j++) {
         int x = navire.premiere_case.x;
         int y = navire.premiere_case.y;
         switch (navire.sens) {
            case 0:
               x -= j;
               break;
            case 1:
               y += j;
               break;
            case 2:
               x += j;
               break;
            case 3:
               y -= j;
               break;
         }
         plateau[x][y] = num_bateau;
      }
      num_bateau++;
   }
}

/**
 * Demande à l'utilisateur d'entrer les coordonnées.
 *
 * @param x La coordonnée en ligne.
 * @param y La coordonnée en colonne.
 */
void saisir_coordonnees(int *x, int *y) {
   printf("Entrez les coordonnées de la case (y puis x) à jouer \n");
   printf("y: ");
   scanf("%d", x);
   printf("x: ");
   scanf("%d", y);
}

/**
 * Vérifie si les coordonnées sont valides en fonction du plateau.
 *
 * @param x La coordonnée en ligne.
 * @param y La coordonnée en colonne.
 * @param taille_plateau La taille du plateau.
 * @return 1 si les coordonnées sont valides, sinon 0.
 */
int verifier_validite_coordonnees(int x, int y, int taille_plateau) {
   if (x < 0 || y < 0 || x >= taille_plateau || y >= taille_plateau) {
      printf("Coordonnées invalides \n");
      return 0;
   }
   return 1;
}

/**
 * Vérifie si le navire est coulé et met à jour le nom du dernier navire coulé.
 *
 * @param prop L'état des cases.
 * @param navires Le tableau de navires.
 * @param num_bateau Le numéro du navire.
 * @param dernier_navire_coule Le nom du dernier navire coulé.
 */
void verifier_navire_coule(int prop[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU],
                           Navire navires[],
                           int num_bateau,
                           char dernier_navire_coule[]) {

   int taille_bateau = navires[num_bateau - 1].taille;
   int coule = 1;
   for (int i = 0; i < taille_bateau; i++) {
      int case_x = navires[num_bateau - 1].premiere_case.x;
      int case_y = navires[num_bateau - 1].premiere_case.y;
      switch (navires[num_bateau - 1].sens) {
         case 0:
            case_x -= i;
            break;
         case 1:
            case_y += i;
            break;
         case 2:
            case_x += i;
            break;
         case 3:
            case_y -= i;
            break;
      }
      if (prop[case_x][case_y] != 1) {
         coule = 0;
         break;
      }
   }
   if (coule) {
      printf("Le navire %s de taille %d a été coulé \n", navires[num_bateau - 1].nom, taille_bateau);
      strcpy(dernier_navire_coule, navires[num_bateau - 1].nom);
   }
}

/**
 * Propose une position au joueur
 *
 * @param plateau Le plateau de jeu
 * @param prop L'état des cases.
 * @param nb_touche Nombre total de coups réussis.
 * @param nb_joue Nombre total de coups joués.
 * @param nb_touche_nav Nombre de coups réussis.
 * @param navires Tableau de navires.
 * @param taille_plateau Taille du plateau de jeu.
 * @param coups_deja_joues Nombre de coups déjà joués.
 */
void proposition_joueur(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU],
                        int prop[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU],
                        int *nb_touche,
                        int *nb_joue,
                        int *nb_touche_nav,
                        Navire navires[],
                        int taille_plateau,
                        int *coups_deja_joues) {
   int x, y;
   saisir_coordonnees(&x, &y);

   if (!verifier_validite_coordonnees(x, y, taille_plateau)) {
      return;
   }

   if (prop[x][y] != 0) {
      printf("Case déjà jouée \n");
      (*coups_deja_joues)++;
      return;
   }

   (*nb_joue)++;
   if (plateau[x][y] == 0) {
      printf("À l'eau \n");
      prop[x][y] = -1;
   } else {
      printf("Touché \n");
      (*nb_touche)++;
      nb_touche_nav[plateau[x][y] - 1]++;
      prop[x][y] = 1;

      verifier_navire_coule(prop, navires, plateau[x][y], dernier_navire_coule);
   }
}

/**
 * Affiche l'entête du plateau de jeu avec les numéros.
 *
 * @param taille_plateau Taille du plateau de jeu.
 */
void affichage_entete(int taille_plateau) {
   printf("  ");
   for (int i = 0; i < taille_plateau; i++) {
      if (i <= 9) {
         printf("%2d", i);
      } else {
         break;
      }
   }
   printf("\n");
}

/**
 * Affiche le plateau de jeu avec les symboles représentant l'état des cases.
 *
 * @param plateau Le plateau de jeu.
 * @param taille_plateau La taille du plateau de jeu.
 */
void affichage_plateau(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau) {
   affichage_entete(taille_plateau);
   for (int i = 0; i < taille_plateau; i++) {
      printf("%2d", i);
      for (int j = 0; j < taille_plateau; j++) {
         if (plateau[i][j] == 0) {
            printf(" .");
         } else if (plateau[i][j] == -1) {
            printf(" o");
         } else {
            printf(" x");
         }
      }
      printf("\n");
   }
}

/**
 * Saisir la taille du plateau de jeu et vérifie sa validité.
 *
 * @return La taille du plateau de jeu saisie.
 */
int saisir_taille_plateau() {
   int taille_plateau;

   do {
      printf("Entrez la taille du plateau de jeu (min 6; max 100): ");
      scanf("%d", &taille_plateau);

      if (taille_plateau < TAILLE_MIN_TABLEAU || taille_plateau > TAILLE_MAX_TABLEAU) {
         printf("Taille invalide. Veuillez entrer une taille entre 6 et 100.\n");
      }
   } while (taille_plateau < TAILLE_MIN_TABLEAU || taille_plateau > TAILLE_MAX_TABLEAU);

   return taille_plateau;
}

/**
 * Affiche les bateaux sur le plateau de jeu  avec leurs numéros
 *
 * @param navires Le tableau de navires.
 * @param plateau Le plateau avec l'emplacements des navires.
 * @param taille_plateau La taille du plateau
 */
void afficher_bateaux(Navire navires[], int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau) {
   affichage_entete(taille_plateau);

   for (int i = 0; i < taille_plateau; i++) {
      printf("%2d", i);

      for (int j = 0; j < taille_plateau; j++) {
         if (plateau[i][j] == 0) {
            printf(" .");
         } else {
            printf(" %d", plateau[i][j]);
         }
      }
      printf("\n");
   }
}

/**
 * Vérifie si tous les bateaux ont été coulés.
 *
 * @param nb_touche_nav Nombre de coups réussis pour chaque navire.
 * @param navires Tableau de navires.
 * @return 1 si tous les bateaux ont été coulés, sinon 0.
 */
int tous_bateaux_coules(int nb_touche_nav[], Navire navires[]) {
   for (int i = 0; i < 5; i++) {
      if (nb_touche_nav[i] != navires[i].taille) {
         return 0;
      }
   }
   return 1;
}
