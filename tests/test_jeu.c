#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../jeu.h"

void test_init_nb_aleatoire() {
   init_nb_aleatoire();
   CU_ASSERT_TRUE(1);
}

void test_nb_aleatoire(void) {
   int max = 10;
   int random = nb_aleatoire(max);
   CU_ASSERT_TRUE(random >= 0 && random < max);
}

void test_est_valide(void) {
   int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU];
   int taille_plateau = 10;

   //Navire Valide
   Navire navire_valide;
   navire_valide.premiere_case.x = 0;
   navire_valide.premiere_case.y = 0;
   navire_valide.taille = 3;
   navire_valide.sens = 2;
   CU_ASSERT_TRUE(est_valide(plateau, taille_plateau, &navire_valide));

   //Navire non valide
   Navire navire_invalide;
   navire_invalide.premiere_case.x = 9;
   navire_invalide.premiere_case.y = 9;
   navire_invalide.taille = 3;
   navire_invalide.sens = 2;
   CU_ASSERT_FALSE(est_valide(plateau, taille_plateau, &navire_invalide));
}

void test_initialisation_plateau() {
   int plateau[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU];
   Navire navires[5];
   int taille_plateau = 10;

   initialisation_plateau(navires, plateau, taille_plateau);

   for (int i = 0; i < 5; i++) {
      Navire navire = navires[i];
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
         CU_ASSERT_TRUE(x >= 0 && x < taille_plateau);
         CU_ASSERT_TRUE(y >= 0 && y < taille_plateau);
         CU_ASSERT_EQUAL(plateau[x][y], i + 1);
      }
   }
}

void test_verifier_validite_coordonnees() {
   int taille_plateau = 10;

   CU_ASSERT_EQUAL(verifier_validite_coordonnees(5, 5, taille_plateau), 1);
   CU_ASSERT_EQUAL(verifier_validite_coordonnees(-1, 5, taille_plateau), 0);
   CU_ASSERT_EQUAL(verifier_validite_coordonnees(11, 5, taille_plateau), 0);
}

void test_verifier_navire_coule() {
   char dernier_navire_coule[100] = "";
   int prop[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU];

   Navire navires[1];
   navires[0].premiere_case.x = 0;
   navires[0].premiere_case.y = 0;
   navires[0].taille = 3;
   navires[0].sens = 2;
   strcpy(navires[0].nom, "PORTE_AVIONS");

   for (int i = 0; i < navires[0].taille; i++) {
      prop[navires[0].premiere_case.x + i][navires[0].premiere_case.y] = 1;
   }

   verifier_navire_coule(prop, navires, 1, dernier_navire_coule);

   CU_ASSERT_STRING_EQUAL(dernier_navire_coule, "PORTE_AVIONS");
}

void test_tous_bateaux_coules() {
   Navire navires[5];
   int nb_touche_nav[5];

   navires[0].taille = 5;
   navires[1].taille = 4;
   navires[2].taille = 3;
   navires[3].taille = 3;
   navires[4].taille = 2;

   for (int i = 0; i < 5; i++) {
      nb_touche_nav[i] = navires[i].taille;
   }
   CU_ASSERT_EQUAL(tous_bateaux_coules(nb_touche_nav, navires), 1);


   nb_touche_nav[4] = 1;
   CU_ASSERT_EQUAL(tous_bateaux_coules(nb_touche_nav, navires), 0);
}


int main() {
   CU_initialize_registry();

   CU_pSuite suite_random = CU_add_suite("Tests de Génération de Nombre Aléatoire", NULL, NULL);
   CU_add_test(suite_random, "Test init_nb_aleatoire", test_init_nb_aleatoire);
   CU_add_test(suite_random, "Test nb_aleatoire", test_nb_aleatoire);

   CU_pSuite suite_jeu = CU_add_suite("Tests d'Initialisation du Plateau de Jeu", NULL, NULL);
   CU_add_test(suite_jeu, "Test est_valide", test_est_valide);
   CU_add_test(suite_jeu, "Test initialisation_plateau", test_initialisation_plateau);

   CU_pSuite suite_validite = CU_add_suite("Test de la fonction verifier_validite_coordonnees", NULL, NULL);
   CU_add_test(suite_validite, "test_verifier_validite_coordonnees", test_verifier_validite_coordonnees);

   CU_pSuite suite_navire_coule = CU_add_suite("Test de la fonction verifier_navire_coule", NULL, NULL);
   CU_add_test(suite_navire_coule, "test_verifier_navire_coule", test_verifier_navire_coule);

   CU_pSuite suite_tous_bateaux_coules = CU_add_suite("Test tous_bateaux_coules", NULL, NULL);
   CU_add_test(suite_tous_bateaux_coules, "test_tous_bateaux_coules", test_tous_bateaux_coules);

   CU_basic_run_tests();
   CU_cleanup_registry();

   return 0;
}
