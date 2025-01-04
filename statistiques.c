#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"
#include "statistiques.h"

FILE *fichier_stats;

/**
 * Calcule le nombre total de coups joués.
 *
 * @param prop Le tableau indiquant l'état des cases.
 * @param taille_plateau Taille du plateau de jeu.
 * @return Nombre total de coups.
 */
int nombre_total_coups_joues(int prop[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau) {
   int coups_joues = 0;
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         if (prop[i][j] != 0) {
            coups_joues++;
         }
      }
   }
   return coups_joues;
}

/**
 * Calcule le nombre total de coups touchés
 *
 * @param plateau Le plateau de jeu avec les navires.
 * @param taille_plateau Taille du plateau de jeu.
 * @return Nombre total de coups touchés.
 */
int nombre_total_coups_touche(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau) {
   int coups_touche = 0;
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         if (plateau[i][j] == 1) {
            coups_touche++;
         }
      }
   }
   return coups_touche;
}

/**
 * Nmbre total de coups dans l'eau
 *
 * @param plateau Le plateau de jeu avec les navires.
 * @param taille_plateau Taille du plateau de jeu.
 * @return Nombre total de coups manqués.
 */
int nombre_total_coups_eau(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau) {
   int coups_eau = 0;
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         if (plateau[i][j] == -1) {
            coups_eau++;
         }
      }
   }
   return coups_eau;
}

/**
 * Calcule le nombre de lettres uniques dans une chaîne de caractères.
 *
 * @param nom_navire La chaîne représentant le nom du navire.
 * @return Nombre de lettres uniques dans le nom du navire.
 */
int nombre_lettres_sans_doublons(char *nom_navire) {
   int lettre_presente[26] = {0};
   int compteur = 0;

   for (int i = 0; nom_navire[i] != '\0'; i++) {
      if (nom_navire[i] >= 'A' && nom_navire[i] <= 'Z') {
         if (!lettre_presente[nom_navire[i] - 'A']) {
            lettre_presente[nom_navire[i] - 'A'] = 1;
            compteur++;
         }
      } else if (nom_navire[i] >= 'a' && nom_navire[i] <= 'z') {
         if (!lettre_presente[nom_navire[i] - 'a']) {
            lettre_presente[nom_navire[i] - 'a'] = 1;
            compteur++;
         }
      }
   }

   return compteur;
}

/**
 * Met à jour le nom du dernier navire coulé.
 *
 * @param nom_navire Nom du navire coulé.
 */
void mettre_a_jour_dernier_navire_coule(char nom_navire[]) {
   strcpy(dernier_navire_coule, nom_navire);
}

/**
 * Écrit les statistiques de jeu dans un fichier.
 *
 * @param nom_fichier Le nom du fichier dans lequel écrire les statistiques.
 * @param coups_joues Nombre total de coups joués.
 * @param nombre_lettres_sans_doublons Le nombre de lettres uniques.
 * @param coups_eau Nombre total de coups à l'eau.
 * @param coups_deja_joues Nombre de coups déjà joués.
 * @param coups_touche Nombre total de coups touchés.
 * @param dernier_navire_coule Nm du dernier navire coulé.
 */
void ecrire_statistiques_dans_fichier(char *nom_fichier, int coups_joues, int nombre_lettres_sans_doublons,
                                      int coups_eau, int coups_deja_joues,
                                      int coups_touche, char dernier_navire_coule[]) {
   fichier_stats = fopen(nom_fichier, "w");
   if (fichier_stats == NULL) {
      fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
      exit(1);
   }

   fprintf(fichier_stats, "--- Statistiques ---\n");
   fprintf(fichier_stats, "Nombre total de coups joués : %d\n", coups_joues);
   fprintf(fichier_stats, "Le nombre de lettres sans doublon du nom du premier navire touché : %d\n", nombre_lettres_sans_doublons);
   fprintf(fichier_stats, "Nombre total de coups 'à l'eau' : %d\n", coups_eau);
   fprintf(fichier_stats, "Coups déjà joués : %d\n", coups_deja_joues);
   fprintf(fichier_stats, "Nombre total de coups 'touchés' : %d\n", coups_touche);
   fprintf(fichier_stats, "Le nom du dernier navire coulé est : %s\n", dernier_navire_coule);

   fclose(fichier_stats);
}