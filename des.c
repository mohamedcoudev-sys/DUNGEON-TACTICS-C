#include <time.h>
#include "des.h"

#define SEUIL_REUSSITE 10
#define ECHEC_CRITIQUE 1
#define REUSSITE_CRITIQUE 20

void initialiserAleatoire(void) {
    srand((unsigned int)time(NULL));
}

int lancerDe(int faces) {
    if (faces < 1) {
        return 0;
    }
    return rand() % faces + 1;
}

int nombreEntre(int min, int max) {
    if (max < min) {
        return min;
    }
    return min + rand() % (max - min + 1);
}

int jetInitiative(combattant c) {
    return lancerDe(20) + c.initiation;
}

ResultatAttaque jetAttaque(void) {
    int jet = lancerDe(20);

    if (jet == ECHEC_CRITIQUE) {
        return ATTAQUE_RATEE;
    }
    if (jet == REUSSITE_CRITIQUE) {
        return ATTAQUE_CRITIQUE;
    }
    if (jet >= SEUIL_REUSSITE) {
        return ATTAQUE_REUSSIE;
    }
    return ATTAQUE_RATEE;
}

int calculerDegats(Arme arme, ResultatAttaque resultat) {
    int degats;

    if (resultat == ATTAQUE_RATEE) {
        return 0;
    }

    degats = nombreEntre(arme.degats_min, arme.degats_max);

    if (resultat == ATTAQUE_CRITIQUE) {
        degats = degats * 2;
    }
    return degats;
}



int peutLancerSort(combattant c) {
    return c.pp >= COUT_SORT;
}

int ppApresSort(int pp) {
    pp = pp - COUT_SORT;
    if (pp < 0) {
        pp = 0;
    }
    return pp;
}

int ppApresRegeneration(int pp) {
    pp = pp + REGEN_PP;
    if (pp > PP_MAX) {
        pp = PP_MAX;
    }
    return pp;
}

int degatsSort(Arme arme) {
    return nombreEntre(arme.degats_min, arme.degats_max) * 2;
}


int estMort(combattant c) {
    return c.pv_actuel <= 0;
}


int choisirAction(combattant c, int manuel) {
    int choix = ACTION_ATTAQUE;

    if (!peutLancerSort(c)) {
        return ACTION_ATTAQUE;
    }

    if (manuel) {
        printf("%s (PV %d, PP %d) - 1 = attaque, 2 = sort (%d PP) : ",
               c.nom, c.pv_actuel, c.pp, COUT_SORT);
        if (scanf("%d", &choix) != 1) {
            choix = ACTION_ATTAQUE;
        }
        if (choix != ACTION_SORT) {
            choix = ACTION_ATTAQUE;
        }
    }
    else {
        choix = ACTION_SORT;
    }
    return choix;
}

void executerAction(combattant equipe[], int attaquant, int cible, int action, char message[]) {
    int degats;
    ResultatAttaque res;

    if (action == ACTION_SORT) {
        degats = degatsSort(equipe[attaquant].arme);
        equipe[attaquant].pp = ppApresSort(equipe[attaquant].pp);
        sprintf(message, "%s lance un sort sur %s : %d degats (PP restants : %d)",
                equipe[attaquant].nom, equipe[cible].nom, degats,
                equipe[attaquant].pp);
    }
    else {
        res = jetAttaque();
        degats = calculerDegats(equipe[attaquant].arme, res);
        if (res == ATTAQUE_RATEE) {
            sprintf(message, "%s attaque %s et rate",
                    equipe[attaquant].nom, equipe[cible].nom);
        }
        else if (res == ATTAQUE_CRITIQUE) {
            sprintf(message, "%s attaque %s : COUP CRITIQUE ! %d degats",
                    equipe[attaquant].nom, equipe[cible].nom, degats);
        }
        else {
            sprintf(message, "%s attaque %s : %d degats",
                    equipe[attaquant].nom, equipe[cible].nom, degats);
        }
    }

    equipe[cible].pv_actuel = equipe[cible].pv_actuel - degats;
    if (equipe[cible].pv_actuel < 0) {
        equipe[cible].pv_actuel = 0;
    }
}

void finDeTour(combattant equipe[]) {
    equipe[HEROS].pp = ppApresRegeneration(equipe[HEROS].pp);
    equipe[MONSTRE].pp = ppApresRegeneration(equipe[MONSTRE].pp);
}

void jouerTour(combattant equipe[], int attaquant, int cible, int manuel) {
    int action;
    char message[TAILLE_MESSAGE];

    if (attaquant != HEROS) {
        manuel = 0;
    }

    action = choisirAction(equipe[attaquant], manuel);
    executerAction(equipe, attaquant, cible, action, message);

    printf("%s\n", message);
    printf("   %s : %d/%d PV\n", equipe[cible].nom,
           equipe[cible].pv_actuel, equipe[cible].pv_max);
}

int jouerCombat(combattant equipe[], int manuel) {
    int initHeros;
    int initMonstre;
    int premier;
    int second;
    int tour = 0;

    initHeros = jetInitiative(equipe[HEROS]);
    initMonstre = jetInitiative(equipe[MONSTRE]);
    if (initHeros >= initMonstre) {
        premier = HEROS;
    }
    else {
        premier = MONSTRE;
    }
    second = 1 - premier;
    printf("%s joue en premier\n", equipe[premier].nom);

    while (!estMort(equipe[HEROS]) && !estMort(equipe[MONSTRE])) {
        tour++;
        printf("\n=== Tour %d ===\n", tour);

        jouerTour(equipe, premier, second, manuel);
        if (!estMort(equipe[second])) {
            jouerTour(equipe, second, premier, manuel);
        }

        finDeTour(equipe);
    }

    if (estMort(equipe[HEROS])) {
        return MONSTRE;
    }
    return HEROS;
}