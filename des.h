#ifndef DES_H
#define DES_H

#include "game.h"

#define COUT_SORT 3
#define PP_MAX 10
#define REGEN_PP 1

#define TAILLE_MESSAGE 200

#define ACTION_ATTAQUE 1
#define ACTION_SORT 2

typedef enum {
    ATTAQUE_RATEE,
    ATTAQUE_REUSSIE,
    ATTAQUE_CRITIQUE
} ResultatAttaque;

void initialiserAleatoire(void);
int lancerDe(int faces);
int nombreEntre(int min, int max);
int jetInitiative(combattant c);
ResultatAttaque jetAttaque(void);
int calculerDegats(Arme arme, ResultatAttaque resultat);


int peutLancerSort(combattant c);
int ppApresSort(int pp);
int ppApresRegeneration(int pp);
int degatsSort(Arme arme);

int estMort(combattant c);
int choisirAction(combattant c, int manuel);
void executerAction(combattant equipe[], int attaquant, int cible, int action, char message[]);
void finDeTour(combattant equipe[]);
void jouerTour(combattant equipe[], int attaquant, int cible, int manuel);
int jouerCombat(combattant equipe[], int manuel);

#endif