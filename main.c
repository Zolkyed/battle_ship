#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "jeu.h"
#include "statistiques.h"

/**
 * Déterminer s'il faut sauvegarder les statistiques
 *
 * @param argc Nombre d'arguments.
 * @param argv Tableau d'arguments.
 * @param sauvegarder_stats Si les statistiques doivent être sauvegardées.
 * @param nom_fichier_sortie Stocker le nom du fichier de sortie.
 * @return 1 si les arguments sont corrects, sinon 0.
 */
int analyser_arguments(int argc, char *argv[], int *sauvegarder_stats, char **nom_fichier_sortie) {
   if (argc >= 2 && strcmp(argv[1], "-S") == 0) {
      if (argc == 3) {
         *sauvegarder_stats = 1;
         *nom_fichier_sortie = argv[2];
      } else {
         fprintf(stderr, "Utilisation : %s -S <fichier_sortie>\n", argv[0]);
         return 0;
      }
   }
   return 1;
}

/**
 * Demande à l'utilisateur de choisir entre deux options.
 *
 * @param action Stocker l'action choisie par l'utilisateur.
 */
void demander_action(int *action) {
   printf("Veuillez choisir une option :\n");
   printf("1. Jouer au jeux\n");
   printf("2. Afficher les bateaux\n");
   printf("Entrez votre choix (1 ou 2) : ");

   scanf("%d", action);

   while (getchar() != '\n');

   if (*action != 1 && *action != 2) {
      printf("Veuillez entrer une option valide 1 ou 2 : \n");
      demander_action(action);
   }
}

/**
 * Demande à l'utilisateur s'il veut rejouer.
 *
 * Demande à l'utilisateur de saisir 'o' pour oui ou 'n' pour non. 
 *
 * @return Le caractère.
 */
char demander_rejouer() {
   char rejouer;
   bool valide = false;

   do {
      printf("Voulez-vous rejouer ? (o pour oui, n pour non): ");
      scanf(" %c", &rejouer);
      if (rejouer == 'o' || rejouer == 'n' || rejouer == 'O' || rejouer == 'N') {
         valide = true;
      } else {
         printf("Réponse invalide.\n");
      }
   } while (!valide);

   return rejouer;
}

/**
 * Lance une partie du jeu de bataille navale.
 *
 * @param taille_plateau La taille du plateau de jeu.
 * @param sauvegarder_stats Indiquant si les statistiques doivent être sauvegardées
 * @param nom_fichier_sortie Nom du fichier dans lequel sauvegarder.
 */
void jouer_partie(int taille_plateau, int sauvegarder_stats, char *nom_fichier_sortie) {
   Navire navires[5];
   int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU] = {0};
   int prop[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU] = {0};
   int coups_deja_joues = 0;
   int nb_touche = 0;
   int nb_joue = 0;
   int nb_touche_nav[5] = {0};
   int action;

   init_nb_aleatoire();
   initialisation_plateau(navires, plateau, taille_plateau);

   demander_action(&action);

   if (action == 2) {
      afficher_bateaux(navires, plateau, taille_plateau);
   }

   while (!tous_bateaux_coules(nb_touche_nav, navires)) {
      proposition_joueur(plateau, prop, &nb_touche, &nb_joue, nb_touche_nav, navires, taille_plateau,
                         &coups_deja_joues);
      affichage_plateau(prop, taille_plateau);
   }

   printf("Toutes les cibles ont été touchées ! Vous avez gagné en %d coups.\n", nb_joue);

   int coups_joues = nombre_total_coups_joues(prop, taille_plateau);
   int coups_eau = nombre_total_coups_eau(prop, taille_plateau);
   int coups_touche = nombre_total_coups_touche(prop, taille_plateau);
   int nombre_lettres_unique = nombre_lettres_sans_doublons(navires[0].nom);

   if (sauvegarder_stats) {
      ecrire_statistiques_dans_fichier(nom_fichier_sortie, coups_joues, nombre_lettres_unique, coups_eau,
                                       coups_deja_joues, coups_touche, dernier_navire_coule);
   }
}
/**
 * Initialise une partie de jeu de bataille navale.
 *
 * @param argc Nmbre d'arguments de la ligne de commande.
 * @param argv Tableau d'arguments de la ligne de commande.
 * @return 0 si le programme s'est exécuté avec succès, sinon 1.
 */
int main(int argc, char *argv[]) {
   int taille_plateau = saisir_taille_plateau();
   int sauvegarder_stats = 0;
   char *nom_fichier_sortie = NULL;
   char rejouer = 'o';

   do {
      if (!analyser_arguments(argc, argv, &sauvegarder_stats, &nom_fichier_sortie)) {
         exit(1);
      }
      jouer_partie(taille_plateau, sauvegarder_stats, nom_fichier_sortie);

      rejouer = demander_rejouer();
   } while (rejouer == 'o' || rejouer == 'O');

   return 0;
}