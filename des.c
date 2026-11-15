#include <time.h>
#include "des.h"

#define SEUIL_REUSSITE 10
#define ECHEC_CRITIQUE 1
#define REUSSITE_CRITIQUE 20

/* Initialise le generateur aleatoire (a appeler une seule fois au debut) */
void initialiserAleatoire(void) {
    srand((unsigned int)time(NULL));
}

/* Lance un de a "faces" faces : retourne un nombre entre 1 et faces */
int lancerDe(int faces) {
    if (faces < 1) {
        return 0;
    }
    return rand() % faces + 1;
}

/* Retourne un nombre aleatoire entre min et max (inclus) */
int nombreEntre(int min, int max) {
    if (max < min) {
        return min;
    }
    return min + rand() % (max - min + 1);
}

/* Initiative = d20 + bonus d'initiation du combattant */
int jetInitiative(combattant c) {
    return lancerDe(20) + c.initiation;
}

/* Jet d'attaque : 1 = rate, 20 = critique, 10 ou plus = reussi */
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

/* Degats de l'arme selon le resultat (rate = 0, critique = x2) */
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


/* ===================== MANA ===================== */

/* Un sort coute COUT_SORT points de pouvoir */
int peutLancerSort(combattant c) {
    return c.pp >= COUT_SORT;
}

/* PP restants apres un sort (jamais en dessous de 0) */
int ppApresSort(int pp) {
    pp = pp - COUT_SORT;
    if (pp < 0) {
        pp = 0;
    }
    return pp;
}

/* PP apres la regeneration de fin de tour (jamais plus de PP_MAX) */
int ppApresRegeneration(int pp) {
    pp = pp + REGEN_PP;
    if (pp > PP_MAX) {
        pp = PP_MAX;
    }
    return pp;
}

/* Un sort touche toujours et fait le double des degats de l'arme */
int degatsSort(Arme arme) {
    return nombreEntre(arme.degats_min, arme.degats_max) * 2;
}

/* ================== TOUR PAR TOUR ================== */

int estMort(combattant c) {
    return c.pv_actuel <= 0;
}

/* Retourne ACTION_ATTAQUE ou ACTION_SORT.
   manuel = 1 : le joueur choisit au clavier
   manuel = 0 : choix automatique (sort s'il reste assez de PP) */
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

/* Un combattant (attaquant) agit contre l'autre (cible).
   equipe[] est un tableau : equipe[HEROS] et equipe[MONSTRE] */
void jouerTour(combattant equipe[], int attaquant, int cible, int manuel) {
    int action;
    int degats;
    ResultatAttaque res;

    /* seul le heros peut etre controle au clavier */
    if (attaquant != HEROS) {
        manuel = 0;
    }

    action = choisirAction(equipe[attaquant], manuel);

    if (action == ACTION_SORT) {
        degats = degatsSort(equipe[attaquant].arme);
        equipe[attaquant].pp = ppApresSort(equipe[attaquant].pp);
        printf("%s lance un sort sur %s : %d degats (PP restants : %d)\n",
               equipe[attaquant].nom, equipe[cible].nom, degats,
               equipe[attaquant].pp);
    }
    else {
        res = jetAttaque();
        degats = calculerDegats(equipe[attaquant].arme, res);
        if (res == ATTAQUE_RATEE) {
            printf("%s attaque %s et rate\n",
                   equipe[attaquant].nom, equipe[cible].nom);
        }
        else if (res == ATTAQUE_CRITIQUE) {
            printf("%s attaque %s : COUP CRITIQUE ! %d degats\n",
                   equipe[attaquant].nom, equipe[cible].nom, degats);
        }
        else {
            printf("%s attaque %s : %d degats\n",
                   equipe[attaquant].nom, equipe[cible].nom, degats);
        }
    }

    equipe[cible].pv_actuel = equipe[cible].pv_actuel - degats;
    if (equipe[cible].pv_actuel < 0) {
        equipe[cible].pv_actuel = 0;
    }
    printf("   %s : %d/%d PV\n", equipe[cible].nom,
           equipe[cible].pv_actuel, equipe[cible].pv_max);
}

/* Boucle principale du combat. Retourne HEROS ou MONSTRE (le vainqueur) */
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

        /* fin du tour : regeneration du mana */
        equipe[HEROS].pp = ppApresRegeneration(equipe[HEROS].pp);
        equipe[MONSTRE].pp = ppApresRegeneration(equipe[MONSTRE].pp);
    }

    if (estMort(equipe[HEROS])) {
        return MONSTRE;
    }
    return HEROS;
}