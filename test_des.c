#include "des.h"

int main(void) {
    combattant hero;
    combattant monstre;
    int i;
    int compteur[6] = {0, 0, 0, 0, 0, 0};
    int initHero, initMonstre;
    ResultatAttaque res;
    int degats;
    combattant equipe[2];
    int vainqueur;

    initialiserAleatoire();

    /* Creation des combattants avec les fonctions de game.c */
    hero = initialiserHero("Arthur", ARME_EPEE);
    monstre = initialiserMonstre("Gobelin", ARME_LANCE);

    /* TEST 1 : le de est-il equilibre ? 6000 lancers de d6 */
    printf("--- Test 1 : 6000 lancers de d6 ---\n");
    for (i = 0; i < 6000; i++) {
        compteur[lancerDe(6) - 1]++;
    }
    for (i = 0; i < 6; i++) {
        printf("Face %d : %d fois\n", i + 1, compteur[i]);
    }

    /* TEST 2 : initiative */
    printf("\n--- Test 2 : initiative ---\n");
    initHero = jetInitiative(hero);
    initMonstre = jetInitiative(monstre);
    printf("%s : %d | %s : %d\n", hero.nom, initHero, monstre.nom, initMonstre);
    if (initHero >= initMonstre)  {
        printf("%s joue en premier\n", hero.nom);
    }
    else {
        printf("%s joue en premier\n", monstre.nom);
    }

    /* TEST 3 : 10 attaques du heros */
    printf("\n--- Test 3 : 10 attaques de %s ---\n", hero.nom);
    for (i = 0; i < 10; i++) {
        res = jetAttaque();
        degats = calculerDegats(hero.arme, res);
        if (res == ATTAQUE_RATEE) {
            printf("Attaque %d : ratee\n", i + 1);
        }
        else if (res == ATTAQUE_CRITIQUE) {
            printf("Attaque %d : COUP CRITIQUE ! %d degats\n", i + 1, degats);
        }
        else  {
            printf("Attaque %d : reussie, %d degats\n", i + 1, degats);
        }
    }

    /* TEST 4 : combat complet (0 = automatique, 1 = le joueur choisit) */
    printf("\n--- Test 4 : combat complet ---\n");
    equipe[HEROS] = hero;
    equipe[MONSTRE] = monstre;
    vainqueur = jouerCombat(equipe, 0);
    printf("\nVictoire de %s !\n", equipe[vainqueur].nom);

    return 0;
}