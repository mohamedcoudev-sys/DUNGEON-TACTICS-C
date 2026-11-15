#include "inputs.h"

/* Retourne 1 si le point (x, y) est dans le rectangle, 0 sinon */
int sourisDansZone(int x, int y, int zoneX, int zoneY, int largeur, int hauteur) {
    if (x < zoneX || x > zoneX + largeur)
        return 0;
    if (y < zoneY || y > zoneY + hauteur)
        return 0;
    return 1;
}

/* Retourne le bouton qui se trouve en (x, y), ou ENTREE_RIEN */
int boutonClique(int x, int y) {
    if (sourisDansZone(x, y, X_BOUTON_ATTAQUER, Y_BOUTON, LARGEUR_BOUTON, HAUTEUR_BOUTON))
        return ENTREE_ATTAQUER;
    if (sourisDansZone(x, y, X_BOUTON_SOIGNER, Y_BOUTON, LARGEUR_BOUTON, HAUTEUR_BOUTON))
        return ENTREE_SOIGNER;
    if (sourisDansZone(x, y, X_BOUTON_VOL, Y_BOUTON, LARGEUR_BOUTON, HAUTEUR_BOUTON))
        return ENTREE_VOL_DE_VIE;
    return ENTREE_RIEN;
}

/* Lit tous les evenements en attente (a appeler une fois par image).
   Retourne ENTREE_QUITTER, un bouton clique, ou ENTREE_RIEN. */
int lireEntree(void) {
    SDL_Event evenement;
    int entree = ENTREE_RIEN;
    int bouton;

    while (SDL_PollEvent(&evenement)) {
        /* croix de la fenetre */
        if (evenement.type == SDL_QUIT)
            return ENTREE_QUITTER;

        /* touche Echap */
        if (evenement.type == SDL_KEYDOWN && evenement.key.keysym.sym == SDLK_ESCAPE)
            return ENTREE_QUITTER;

        /* clic gauche : on regarde s'il est sur un bouton */
        if (evenement.type == SDL_MOUSEBUTTONDOWN && evenement.button.button == SDL_BUTTON_LEFT) {
            bouton = boutonClique(evenement.button.x, evenement.button.y);
            if (bouton != ENTREE_RIEN)
                entree = bouton;
        }
    }
    return entree;
}