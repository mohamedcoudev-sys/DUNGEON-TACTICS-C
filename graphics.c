#include "graphics.h"
#include "inputs.h"
#include "des.h"

#define CHEMIN_POLICE "assets/font.ttf"
#define TAILLE_POLICE 16


Graphique initialiserGraphique(void) {
    Graphique g;

    g.fenetre = NULL;
    g.rendu = NULL;
    g.police = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return g;
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
        printf("Erreur IMG_Init : %s\n", IMG_GetError());
        return g;
    }
    if (TTF_Init() != 0) {
        printf("Erreur TTF_Init : %s\n", TTF_GetError());
        return g;
    }

    g.fenetre = SDL_CreateWindow("Dungeon Tactics",
                                 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 LARGEUR_FENETRE, HAUTEUR_FENETRE,
                                 SDL_WINDOW_SHOWN);
    if (g.fenetre == NULL) {
        printf("Erreur fenetre : %s\n", SDL_GetError());
        return g;
    }

    g.rendu = SDL_CreateRenderer(g.fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (g.rendu == NULL) {
        g.rendu = SDL_CreateRenderer(g.fenetre, -1, SDL_RENDERER_SOFTWARE);
    }
    if (g.rendu == NULL) {
        printf("Erreur rendu : %s\n", SDL_GetError());
        return g;
    }

    g.police = TTF_OpenFont(CHEMIN_POLICE, TAILLE_POLICE);
    if (g.police == NULL) {
        printf("Erreur police (%s) : %s\n", CHEMIN_POLICE, TTF_GetError());
    }
    return g;
}

int graphiqueValide(Graphique g)
{
    return g.fenetre != NULL && g.rendu != NULL && g.police != NULL;
}


void libererGraphique(Graphique g)
{
    if (g.police != NULL) {
        TTF_CloseFont(g.police);
    }
    if (g.rendu != NULL) {
        SDL_DestroyRenderer(g.rendu);
    }
    if (g.fenetre != NULL) {
        SDL_DestroyWindow(g.fenetre);
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


void initialiserPlateau(int plateau[LIGNES][COLONNES])
{
    int l, c;

    for (l = 0; l < LIGNES; l++) {
        for (c = 0; c < COLONNES; c++) {
            plateau[l][c] = CASE_SOL;
        }
    }
}

void initialiserEntites(int entites[LIGNES][COLONNES])
{
    int l, c;

    for (l = 0; l < LIGNES; l++) {
        for (c = 0; c < COLONNES; c++) {
            entites[l][c] = CASE_VIDE;
        }
    }
}


void effacerEcran(Graphique g)
{
    SDL_SetRenderDrawColor(g.rendu, 0, 0, 0, 255);
    SDL_RenderClear(g.rendu);
}

void afficherEcran(Graphique g)
{
    SDL_RenderPresent(g.rendu);
}

void dessinerCadre(Graphique g, int x, int y, int largeur, int hauteur)
{
    SDL_Rect r;

    r.x = x;
    r.y = y;
    r.w = largeur;
    r.h = hauteur;
    SDL_SetRenderDrawColor(g.rendu, 255, 255, 255, 255);
    SDL_RenderDrawRect(g.rendu, &r);
}

void dessinerTexte(Graphique g, const char *texte, int x, int y)
{
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect destination;
    int w = 0;
    int h = 0;

    if (g.police == NULL || texte[0] == '\0') {
        return;
    }
    surface = TTF_RenderUTF8_Blended(g.police, texte, blanc);
    if (surface == NULL) {
        return;
    }
    texture = SDL_CreateTextureFromSurface(g.rendu, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        return;
    }

    TTF_SizeUTF8(g.police, texte, &w, &h);
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;

    SDL_RenderCopy(g.rendu, texture, NULL, &destination);
    SDL_DestroyTexture(texture);
}


void dessinerBandeau(Graphique g, const char *tour)
{
    dessinerCadre(g, 10, 10, 880, 50);
    dessinerTexte(g, "[ DONJON & DRAGONS - TOUR PAR TOUR ]", 25, 25);
    dessinerTexte(g, tour, 640, 25);

    dessinerCadre(g, 10, 70, 880, 440);
}


void dessinerCarte(Graphique g, combattant c, int estHeros)
{
    char texte[100];

    dessinerCadre(g, 25, 85, 270, 410);
    dessinerTexte(g, "CARTE DE COMBATTANT", 60, 97);

    /* Cadre du portrait */
    dessinerCadre(g, 40, 125, 240, 180);
    dessinerTexte(g, "[ PORTRAIT DE", 95, 180);
    if (estHeros) {
        dessinerTexte(g, "L'HÉROS ]", 115, 205);
    }
    else {
        dessinerTexte(g, "MONSTRE ]", 113, 205);
    }

     
    sprintf(texte, "Nom   : %s", c.nom);
    dessinerTexte(g, texte, 45, 325);

    if (estHeros) {
        dessinerTexte(g, "Type  : Héros", 45, 355);
    }
    else {
        dessinerTexte(g, "Type  : Monstre", 45, 355);
    }

    sprintf(texte, "Arme  : %s", c.arme.nom);
    dessinerTexte(g, texte, 45, 385);

    sprintf(texte, "PV    : %d / %d", c.pv_actuel, c.pv_max);
    dessinerTexte(g, texte, 45, 415);

    sprintf(texte, "PP    : %d / %d", c.pp, PP_MAX);
    dessinerTexte(g, texte, 45, 445);
}


void dessinerPlateau(Graphique g, int plateau[LIGNES][COLONNES])
{
    int l, c, x, y;
    char texte[20];

    dessinerTexte(g, "[ PLATEAU DE JEU (Grille) ]", 320, 97);

    for (l = 0; l < LIGNES; l++) {
        for (c = 0; c < COLONNES; c++) {
            x = X_PLATEAU + c * LARGEUR_CASE;
            y = Y_PLATEAU + l * HAUTEUR_CASE;
            if (plateau[l][c] == CASE_MUR) {
                dessinerTexte(g, "( mur )", x, y);
            }
            else {
                sprintf(texte, "( %d,%d )", c, l);
                dessinerTexte(g, texte, x, y);
            }
        }
    }
}


void dessinerEntites(Graphique g, int entites[LIGNES][COLONNES], combattant equipe[])
{
    int l, c, i, x, y;

    for (l = 0; l < LIGNES; l++) {
        for (c = 0; c < COLONNES; c++) {
            x = X_PLATEAU + c * LARGEUR_CASE;
            y = Y_PLATEAU + l * HAUTEUR_CASE;
            i = entites[l][c];

            if (i == CASE_VIDE) {
                dessinerTexte(g, "[ . ]", x + 10, y + 22);
            }
            else {
                if (i == HEROS) {
                    dessinerTexte(g, "[H]", x + 14, y + 22);
                }
                else {
                    dessinerTexte(g, "[M]", x + 14, y + 22);
                }
                dessinerTexte(g, equipe[i].nom, x, y + 44);
            }
        }
    }
}


void dessinerJet(Graphique g, const char *message)
{
    dessinerTexte(g, "JET DE DÉS D'ATTAQUE :", 320, 400);
    dessinerTexte(g, message, 320, 430);
}


void dessinerBoutons(Graphique g)
{
    dessinerCadre(g, 10, 520, 880, 60);
    dessinerTexte(g, "BOUTONS D'ACTION :", 25, 540);
    dessinerTexte(g, "[ ⚔ Attaquer ]", X_BOUTON_ATTAQUER, 540);
    dessinerTexte(g, "[ ✚ Sort Soin ]", X_BOUTON_SOIGNER, 540);
    dessinerTexte(g, "[ ❤ Vol de PV ]", X_BOUTON_VOL, 540);
    dessinerTexte(g, "Échap = quitter", 740, 540);
}