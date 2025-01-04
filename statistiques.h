#ifndef STATISTIQUES_H
#define STATISTIQUES_H


int nombre_total_coups_joues(int prop[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau);

int nombre_total_coups_touche(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau);

int nombre_total_coups_eau(int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU], int taille_plateau);

void mettre_a_jour_dernier_navire_coule(char nom_navire[]);

int nombre_lettres_sans_doublons(char *nom_navire);

void ecrire_statistiques_dans_fichier(char *nom_fichier, int coups_joues, int nombre_lettres_sans_doublons,
                                      int coups_eau, int coups_deja_joues,
                                      int coups_touche, char dernier_navire_coule[]);

#endif
