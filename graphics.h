#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"

/* Taille de la fenetre (en pixels) */
#define LARGEUR_FENETRE 900
#define HAUTEUR_FENETRE 600

/* Taille du plateau (en cases) */
#define LIGNES 2
#define COLONNES 3

/* Position du plateau dans la fenetre et taille d'une case (en pixels) */
#define X_PLATEAU 330
#define Y_PLATEAU 135
#define LARGEUR_CASE 150
#define HAUTEUR_CASE 100

/* Contenu d'une case du plateau */
#define CASE_SOL 0
#define CASE_MUR 1

/* Contenu d'une case de la grille des entites */
#define CASE_VIDE -1

/* Tout ce dont SDL a besoin pour dessiner.
   On passe cette structure par valeur : elle ne contient que des pointeurs. */
typedef struct
{
    SDL_Window *fenetre;
    SDL_Renderer *rendu;
    TTF_Font *police;
} Graphique;

/* Ouvre SDL, SDL_image, SDL_ttf et la fenetre.
   Verifier ensuite avec graphiqueValide(). */
Graphique initialiserGraphique(void);
int graphiqueValide(Graphique g);
void libererGraphique(Graphique g);

/* Remplit les deux grilles (plateau tout en sol, entites vides) */
void initialiserPlateau(int plateau[LIGNES][COLONNES]);
void initialiserEntites(int entites[LIGNES][COLONNES]);

/* Outils de dessin (tout est en blanc sur fond noir) */
void effacerEcran(Graphique g);
void afficherEcran(Graphique g);
void dessinerCadre(Graphique g, int x, int y, int largeur, int hauteur);
void dessinerTexte(Graphique g, const char *texte, int x, int y);

/* Les zones de l'ecran : a appeler entre effacerEcran() et afficherEcran() */
void dessinerBandeau(Graphique g, const char *tour);
void dessinerCarte(Graphique g, combattant c, int estHeros);
void dessinerPlateau(Graphique g, int plateau[LIGNES][COLONNES]);
void dessinerEntites(Graphique g, int entites[LIGNES][COLONNES], combattant equipe[]);
void dessinerJet(Graphique g, const char *message);
void dessinerBoutons(Graphique g);

#endif