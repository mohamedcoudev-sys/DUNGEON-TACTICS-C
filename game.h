#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Positions dans le tableau equipe[] */
#define HEROS 0
#define MONSTRE 1

/* Structure et enumeration des armes, monstres et heros */

typedef enum
{
    ARME_ARC,
    ARME_EPEE,
    ARME_LANCE,
    ARME_BATON_MAGE,
    ARME_HACHE
} TypeArme;

typedef struct
{
    char nom[30];
    int degats_min;
    int degats_max;
} Arme;

/* Structure pour un monstre ou un heros
   pp = points de pouvoir (mana), utilises pour lancer des sorts */

typedef struct
{
    char nom[30];
    int xp;
    int pv_max;
    int pv_actuel;
    int pp;
    Arme arme;
    int initiation;
} combattant;

/* Fonctions d'initialisation du module game.
   Elles retournent la structure creee (pas de pointeur a manipuler) :
   hero = initialiserHero("Arthur", ARME_EPEE); */

Arme initialiserArme(TypeArme type);
combattant initialiserStatistiques(const char *nom, Arme arme, int pv, int pp, int initiation);
combattant initialiserHero(const char *nom, TypeArme typearme);
combattant initialiserMonstre(const char *nom, TypeArme typearme);

#endif