#include "graphics.h"

/* Ouvre la fenetre avec le plateau, le heros (bleu) et le monstre (rouge).
   Fermer la fenetre pour quitter. */
int main(int argc, char *argv[])
{
    Graphique g;
    int plateau[LIGNES][COLONNES];
    int entites[LIGNES][COLONNES];
    combattant equipe[2];
    int continuer = 1;
    SDL_Event evenement;

    (void)argc;
    (void)argv;

    g = initialiserGraphique();
    if (!graphiqueValide(g)) {
        libererGraphique(g);
        return 1;
    }

    initialiserPlateau(plateau);
    initialiserEntites(entites);
    equipe[HEROS] = initialiserHero("Arthur", ARME_EPEE);
    equipe[MONSTRE] = initialiserMonstre("Gobelin", ARME_LANCE);
    entites[0][0] = HEROS;
    entites[1][2] = MONSTRE;

    while (continuer) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                continuer = 0;
            }
        }
        effacerEcran(g);
        dessinerPlateau(g, plateau);
        dessinerEntites(g, entites, equipe);
        afficherEcran(g);
        SDL_Delay(16);
    }

    libererGraphique(g);
    return 0;
}