#include "des.h"

int main(void)
{
    char nom[30];
    int choix = 2;
    TypeArme arme = ARME_EPEE;
    combattant equipe[2];
    int vainqueur;

    initialiserAleatoire();

    printf("=== DUNGEON TACTICS ===\n\n");
    printf("Nom du heros : ");
    if (scanf("%29s", nom) != 1) {
        strcpy(nom, "Arthur");
    }

    printf("\nChoisis ton arme :\n");
    printf("1 = Arc | 2 = Epee | 3 = Lance | 4 = Baton de mage | 5 = Hache\n");
    printf("Ton choix : ");
    if (scanf("%d", &choix) != 1 || choix < 1 || choix > 5) {
        choix = 2;
    }
    arme = (TypeArme)(choix - 1);

    equipe[HEROS] = initialiserHero(nom, arme);
    equipe[MONSTRE] = initialiserMonstre("Gobelin", ARME_LANCE);

    printf("\n%s (%s) affronte %s !\n", equipe[HEROS].nom,
           equipe[HEROS].arme.nom, equipe[MONSTRE].nom);

    vainqueur = jouerCombat(equipe, 1);

    if (vainqueur == HEROS) {
        printf("\nVictoire ! %s a vaincu %s.\n", equipe[HEROS].nom, equipe[MONSTRE].nom);
    }
    else {
        printf("\nDefaite... %s a ete vaincu par %s.\n", equipe[HEROS].nom, equipe[MONSTRE].nom);
    }
    return 0;
}