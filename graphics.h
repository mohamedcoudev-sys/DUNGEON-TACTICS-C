#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"

#define LARGEUR_FENETRE 900
#define HAUTEUR_FENETRE 600

#define LIGNES 2
#define COLONNES 3

#define X_PLATEAU 330
#define Y_PLATEAU 135
#define LARGEUR_CASE 150
#define HAUTEUR_CASE 100

#define CASE_SOL 0
#define CASE_MUR 1

#define CASE_VIDE -1

typedef struct
{
    SDL_Window *fenetre;
    SDL_Renderer *rendu;
    TTF_Font *police;
} Graphique;

Graphique initialiserGraphique(void);
int graphiqueValide(Graphique g);
void libererGraphique(Graphique g);

void initialiserPlateau(int plateau[LIGNES][COLONNES]);
void initialiserEntites(int entites[LIGNES][COLONNES]);

void effacerEcran(Graphique g);
void afficherEcran(Graphique g);
void dessinerCadre(Graphique g, int x, int y, int largeur, int hauteur);
void dessinerTexte(Graphique g, const char *texte, int x, int y);

void dessinerBandeau(Graphique g, const char *tour);
void dessinerCarte(Graphique g, combattant c, int estHeros);
void dessinerPlateau(Graphique g, int plateau[LIGNES][COLONNES]);
void dessinerEntites(Graphique g, int entites[LIGNES][COLONNES], combattant equipe[]);
void dessinerJet(Graphique g, const char *message);
void dessinerBoutons(Graphique g);

#endif