#ifndef INPUTS_H
#define INPUTS_H

#include <SDL2/SDL.h>

#define ENTREE_RIEN 0
#define ENTREE_QUITTER 1
#define ENTREE_ATTAQUER 2
#define ENTREE_SOIGNER 3
#define ENTREE_VOL_DE_VIE 4


#define Y_BOUTON 530
#define HAUTEUR_BOUTON 40
#define LARGEUR_BOUTON 150
#define X_BOUTON_ATTAQUER 210
#define X_BOUTON_SOIGNER 380
#define X_BOUTON_VOL 560

int sourisDansZone(int x, int y, int zoneX, int zoneY, int largeur, int hauteur);
int boutonClique(int x, int y);
int lireEntree(void);

#endif