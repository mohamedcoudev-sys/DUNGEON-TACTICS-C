#include "des.h"
#include "graphics.h"
#include "inputs.h"

#define DELAI_MONSTRE 800

/* Position de depart des combattants sur la grille (ligne, colonne) */
#define LIGNE_HEROS 0
#define COL_HEROS 0
#define LIGNE_MONSTRE 1
#define COL_MONSTRE 2

int main(int argc, char *argv[])
{
    Graphique g;
    int plateau[LIGNES][COLONNES];
    int entites[LIGNES][COLONNES];
    combattant equipe[2];
    char message[TAILLE_MESSAGE];
    char tour[TAILLE_MESSAGE];
    int continuer = 1;
    int combatFini = 0;
    int premier;
    int actif;
    int action;
    int entree;
    Uint32 tempsMonstre;

    (void)argc;
    (void)argv;

    initialiserAleatoire();

    /* ---------- Initialisation ---------- */
    g = initialiserGraphique();
    if (!graphiqueValide(g)) {
        libererGraphique(g);
        return 1;
    }

    initialiserPlateau(plateau);
    initialiserEntites(entites);
    equipe[HEROS] = initialiserHero("Arthur", ARME_EPEE);
    equipe[MONSTRE] = initialiserMonstre("Gobelin", ARME_LANCE);
    entites[LIGNE_HEROS][COL_HEROS] = HEROS;
    entites[LIGNE_MONSTRE][COL_MONSTRE] = MONSTRE;

    /* L'initiative decide qui joue en premier */
    if (jetInitiative(equipe[HEROS]) >= jetInitiative(equipe[MONSTRE])) {
        premier = HEROS;
    }
    else {
        premier = MONSTRE;
    }
    actif = premier;
    tempsMonstre = SDL_GetTicks() + DELAI_MONSTRE;
    sprintf(message, "%s joue en premier", equipe[premier].nom);

    /* ---------- Boucle principale (environ 60 images par seconde) ---------- */
    while (continuer) {
        action = 0;

        /* 1. Evenements : tout est lu dans inputs.c */
        entree = lireEntree();

        if (entree == ENTREE_QUITTER) {
            continuer = 0;
        }

        /* Les boutons ne marchent que pendant le tour du heros */
        if (!combatFini && actif == HEROS) {
            if (entree == ENTREE_ATTAQUER) {
                action = ACTION_ATTAQUE;
            }
            if (entree == ENTREE_SOIGNER) {
                sprintf(message, "Sort Soin : pas encore programmé");
            }
            if (entree == ENTREE_VOL_DE_VIE) {
                sprintf(message, "Vol de PV : pas encore programmé");
            }
        }

        /* 2. Mise a jour : le monstre joue tout seul apres une courte pause */
        if (!combatFini && actif == MONSTRE && SDL_GetTicks() >= tempsMonstre) {
            action = choisirAction(equipe[MONSTRE], 0);
        }

        if (action != 0) {
            executerAction(equipe, actif, 1 - actif, action, message);

            if (estMort(equipe[1 - actif])) {
                combatFini = 1;
                if (estMort(equipe[MONSTRE])) {
                    entites[LIGNE_MONSTRE][COL_MONSTRE] = CASE_VIDE;
                }
                else {
                    entites[LIGNE_HEROS][COL_HEROS] = CASE_VIDE;
                }
            }
            else {
                actif = 1 - actif;
                if (actif == premier) {
                    finDeTour(equipe);
                }
                tempsMonstre = SDL_GetTicks() + DELAI_MONSTRE;
            }
        }

        /* 3. Texte en haut a droite */
        if (combatFini) {
            if (estMort(equipe[MONSTRE])) {
                sprintf(tour, "VICTOIRE !");
            }
            else {
                sprintf(tour, "DÉFAITE...");
            }
        }
        else if (actif == HEROS) {
            sprintf(tour, "Tour : Héros");
        }
        else {
            sprintf(tour, "Tour : Monstre");
        }

        /* 4. Dessin */
        effacerEcran(g);
        dessinerBandeau(g, tour);
        dessinerCarte(g, equipe[actif], actif == HEROS);
        dessinerPlateau(g, plateau);
        dessinerEntites(g, entites, equipe);
        dessinerJet(g, message);
        dessinerBoutons(g);
        afficherEcran(g);

        SDL_Delay(16);
    }

    libererGraphique(g);
    return 0;
}