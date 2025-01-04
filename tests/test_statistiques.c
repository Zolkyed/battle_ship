#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../jeu.h"
#include "../statistiques.h"

void test_nombre_lettres_sans_doublons_vide() {
   char nom_navire[] = "";
   int expected_unique_letters = 0;
   int result = nombre_lettres_sans_doublons(nom_navire);

   CU_ASSERT_EQUAL(result, expected_unique_letters);
}

void test_nombre_lettres_sans_doublons_minuscules() {
   char nom_navire[] = "Croiseur";
   int expected_unique_letters = 7;
   int result = nombre_lettres_sans_doublons(nom_navire);

   CU_ASSERT_EQUAL(result, expected_unique_letters);
}

void test_mettre_a_jour_dernier_navire_coule() {
   char nom_navire[] = "Croiseur";
   mettre_a_jour_dernier_navire_coule(nom_navire);
   CU_ASSERT_STRING_EQUAL(dernier_navire_coule, nom_navire);

   char nouveau_nom_navire[] = "Torpilleur";
   mettre_a_jour_dernier_navire_coule(nouveau_nom_navire);
   CU_ASSERT_STRING_EQUAL(dernier_navire_coule, nouveau_nom_navire);
}


void test_ecrire_statistiques_dans_fichier() {
   char *nom_fichier = "test_statistiques.txt";
   int coups_joues = 10;
   int nombre_lettres_sans_doublons = 5;
   int coups_eau = 2;
   int coups_deja_joues = 15;
   int coups_touche = 5;
   char dernier_navire_coule[] = "Torpilleur";

   ecrire_statistiques_dans_fichier(nom_fichier, coups_joues, nombre_lettres_sans_doublons,
                                    coups_eau, coups_deja_joues, coups_touche, dernier_navire_coule);

   FILE *fichier = fopen(nom_fichier, "r");
   CU_ASSERT_PTR_NOT_NULL(fichier);

   fclose(fichier);
}


int main() {
   CU_initialize_registry();

   CU_pSuite suite_lettres = CU_add_suite("Tests pour nombre_lettres_sans_doublons", NULL, NULL);
   CU_add_test(suite_lettres, "test_nombre_lettres_sans_doublons_vide", test_nombre_lettres_sans_doublons_vide);
   CU_add_test(suite_lettres, "test_nombre_lettres_sans_doublons_minuscules", test_nombre_lettres_sans_doublons_minuscules);

   CU_pSuite suite_statistiques = CU_add_suite("Tests pour les fonctions de statistiques", NULL, NULL);
   CU_add_test(suite_statistiques, "test_mettre_a_jour_dernier_navire_coule", test_mettre_a_jour_dernier_navire_coule);
   CU_add_test(suite_statistiques, "test_ecrire_statistiques_dans_fichier", test_ecrire_statistiques_dans_fichier);

   CU_basic_run_tests();
   CU_cleanup_registry();

   return CU_get_error();
}
