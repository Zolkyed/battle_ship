prog=../bataille_navale
premiere_ligne="Taille invalide. Veuillez entrer une taille entre 6 et 100."
fichier="sortie.txt"
fichier2="test.txt"

@test "test0 : Sans aucune entree, afficher aide" {
    skip
    run ./$prog
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "$premiere_ligne" ]
}

@test "test : Vérifier le tableau de jeu" {
    skip
    run ./$prog

    echo "6"          # Taille du plateau de jeu
    echo "1"          # L'option d'affichage
    echo "0"          # Coordonnée y
    echo "0"          # Coordonnée x

    sortie_attendue='
      0 1 2 3 4 5
    0 o . . . . .
    1 . . . . . .
    2 . . . . . .
    3 . . . . . .
    4 . . . . . .
    5 . . . . . .'

    assert_output -p "$sortie_attendue"
}

@test "test2 : Avec argument -S" {
    skip
    run ./$prog -S $fichier

    assert [ -f "$fichier" ]
}


