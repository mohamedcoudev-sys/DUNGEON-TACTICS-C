#include "game.h"

#define HERO_PV 100
#define HERO_PP 6
#define HERO_INITIATION 3

#define MONSTRE_PV 60
#define MONSTRE_PP 4
#define MONSTRE_INITIATION 1

Arme initialiserArme(TypeArme type)
{
    Arme arme;

    switch (type)
    {
        case ARME_ARC:
            strcpy(arme.nom, "Arc");
            arme.degats_min = 4;
            arme.degats_max = 8;
            break;
        case ARME_EPEE:
            strcpy(arme.nom, "Epee");
            arme.degats_min = 5;
            arme.degats_max = 10;
            break;
        case ARME_LANCE:
            strcpy(arme.nom, "Lance");
            arme.degats_min = 5;
            arme.degats_max = 9;
            break;
        case ARME_BATON_MAGE:
            strcpy(arme.nom, "Baton de mage");
            arme.degats_min = 3;
            arme.degats_max = 7;
            break;
        case ARME_HACHE:
            strcpy(arme.nom, "Hache");
            arme.degats_min = 6;
            arme.degats_max = 12;
            break;
        default:
            strcpy(arme.nom, "Poings");
            arme.degats_min = 1;
            arme.degats_max = 3;
            break;
    }
    return arme;
}

combattant initialiserStatistiques(const char *nom, Arme arme, int pv, int pp, int initiation)
{
    combattant c;

    strncpy(c.nom, nom, sizeof(c.nom) - 1);
    c.nom[sizeof(c.nom) - 1] = '\0';
    c.xp = 0;
    c.pv_max = pv;
    c.pv_actuel = pv;
    c.pp = pp;
    c.arme = arme;
    c.initiation = initiation;
    return c;
}

combattant initialiserHero(const char *nom, TypeArme typearme)
{
    return initialiserStatistiques(nom, initialiserArme(typearme),
                                   HERO_PV, HERO_PP, HERO_INITIATION);
}

combattant initialiserMonstre(const char *nom, TypeArme typearme)
{
    return initialiserStatistiques(nom, initialiserArme(typearme),
                                   MONSTRE_PV, MONSTRE_PP, MONSTRE_INITIATION);
}