# Compilation
# --------
CC=gcc
CFLAGS=-Wall

# Build
# -----
build: compile link

compile: main.o jeu.o statistiques.o
	$(CC) $(CFLAGS) -o bataille_navale $^

link: bataille_navale

bataille_navale: main.o jeu.o statistiques.o
	$(CC) $(CFLAGS) -o $@ $^

# Test
# ----
test: jeu_cunits statistiques_cunits bats_tests
	./jeu_cunits
	./statistiques_cunits

jeu_cunits: ./tests/test_jeu.c jeu.c
	$(CC) $(CFLAGS) $^ -o $@ -lcunit

statistiques_cunits: ./tests/test_statistiques.c jeu.c statistiques.c
	$(CC) $(CFLAGS) $^ -o $@ -lcunit

bats_tests:
	bats tests/bataille_navale.bats

# HTML
# ---------------
html: README.md
	pandoc -s README.md -o README.html --css=misc/github-pandoc.css --metadata title="README"

# Clean
# -----
clean:
	rm -f bataille_navale *.o README.html