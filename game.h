#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEROS 0
#define MONSTRE 1


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



Arme initialiserArme(TypeArme type);
combattant initialiserStatistiques(const char *nom, Arme arme, int pv, int pp, int initiation);
combattant initialiserHero(const char *nom, TypeArme typearme);
combattant initialiserMonstre(const char *nom, TypeArme typearme);

#endif