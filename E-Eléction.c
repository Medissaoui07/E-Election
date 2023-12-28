#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELECTIONS 10
#define MAX_CANDIDATS 10

// Structure pour stocker les informations du candidat
struct candidat {
    char nom[50];
    char prenom[50];
    int votes;
};

// Structure pour stocker les informations des administrateurs
struct Admin {
    char nom[50];
    char prenom[50];
};

// Structure pour stocker les informations de l'élection
struct Election {
    char titre[50];
    int annee;
    struct candidat candidats[MAX_CANDIDATS];
    int nbCandidats;
};

// Fonction pour créer un compte administrateur
struct Admin creerAdmin() {
    struct Admin admin;
    printf("Donner le nom de l'admin: ");
    scanf("%s", admin.nom);
    printf("Donner le prénom de l'admin: ");
    scanf("%s", admin.prenom);
    return admin;
}

// Fonction pour créer un compte candidat
struct candidat creercandidat() {
    struct candidat candidat;
    printf("Donner le nom du candidat: ");
    scanf("%s", candidat.nom);
    printf("Donner le prénom du candidat: ");
    scanf("%s", candidat.prenom);
    candidat.votes = 0;
    return candidat;
}

// Fonction pour créer une élection
void creerElection(struct Election *elections, int *nbElections) {
    printf("Entrez le titre de l'election: ");
    scanf("%s", elections[*nbElections].titre);

    printf("Entrez l'annee de l'election: ");
    scanf("%d", &elections[*nbElections].annee);

    printf("Entrez le nombre de candidats: ");
    scanf("%d", &elections[*nbElections].nbCandidats);

    for (int i = 0; i < elections[*nbElections].nbCandidats; i++) {
        elections[*nbElections].candidats[i] = creercandidat();
    }

    sauvegarderHistorique(elections[*nbElections - 1]); // Call the function to save history

    (*nbElections)++;
}

// Fonction pour mettre à jour les informations des candidats
void miseAJourCandidat(struct candidat *candidat) {
    printf("Entrez le nouveau nom du candidat: ");
    scanf("%s", candidat->nom);

    printf("Entrez le nouveau prénom du candidat: ");
    scanf("%s", candidat->prenom);
}

// Fonction pour afficher les détails d'une élection
void afficherDetailsElection(struct Election election) {
    printf("Titre: %s\n", election.titre);
    printf("Année: %d\n", election.annee);
    printf("Nombre de candidats: %d\n", election.nbCandidats);
    for (int i = 0; i < election.nbCandidats; i++) {
        printf("\nDétails du candidat %d:\n", i + 1);
        printf("Nom: %s\n", election.candidats[i].nom);
        printf("Prénom: %s\n", election.candidats[i].prenom);
        printf("Votes: %d\n", election.candidats[i].votes);
    }
}

// Fonction pour voter pour un candidat dans une élection
void voterPourCandidat(struct Election *election) {
    printf("Choisissez le candidat pour lequel vous voulez voter (de 1 à %d): ", election->nbCandidats);
    int choixCandidat;
    scanf("%d", &choixCandidat);

    // Vérifiez si le choix est valide
    if (choixCandidat >= 1 && choixCandidat <= election->nbCandidats) {
        // Incrémentez le nombre de votes pour le candidat choisi
        election->candidats[choixCandidat - 1].votes++;
        printf("Vote enregistré avec succès!\n");
    } else {
        printf("Choix invalide. Veuillez choisir un candidat valide.\n");
    }
}

// Fonction pour afficher le résultat d'une élection
void afficherResultatElection(struct Election *election) {
    printf("\nRésultats de l'élection \"%s\" (%d):\n", election->titre, election->annee);
    for (int i = 0; i < election->nbCandidats; i++) {
        printf("\nPosition %d:\n", i + 1);
        printf("Nom: %s\n", election->candidats[i].nom);
        printf("Prénom: %s\n", election->candidats[i].prenom);
        printf("Votes: %d\n", election->candidats[i].votes);
    }
}

// Fonction pour gérer une élection
void gererElection(struct Election *election) {
    int choix;
    do {
        printf("\nMenu de gestion de l'élection:\n");
        printf("1. Afficher les détails de l'élection\n");
        printf("2. Voter pour un candidat\n");
        printf("3. Quitter la gestion de l'élection\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // Afficher les détails de l'élection
                afficherDetailsElection(*election);
                break;
            case 2:
                // Voter pour un candidat
                voterPourCandidat(election);
                break;
            case 3:
                printf("Fin de la gestion de l'élection.\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
        }
    } while (choix != 3);
}

// Fonction pour afficher la liste des votes pour une élection
void afficherListeVotes(struct Election *election) {
    printf("\nListe des votes pour l'élection \"%s\" (%d):\n", election->titre, election->annee);
    for (int i = 0; i < election->nbCandidats; i++) {
        printf("\nVotes pour le candidat %s (%s): %d\n", election->candidats[i].nom,
               election->candidats[i].prenom, election->candidats[i].votes);
    }
}

// Fonction pour sauvegarder l'historique dans un fichier
void sauvegarderHistorique(struct Election election) {
    FILE *file = fopen("election_history.txt", "a");
    if (file != NULL) {
        fprintf(file, "Titre: %s, Année: %d, Nombre de candidats: %d\n", 
            election.titre, 
            election.annee, 
            election.nbCandidats);
        fclose(file);
    } else {
        printf("Erreur lors de l'écriture dans le fichier d'historique.\n");
    }
}

int main() {
    struct Election elections[MAX_ELECTIONS];
    struct Admin admin;
    struct candidat candidat;
    int nbElections = 0;

    int choix;
    do {
        printf("\nMenu:\n");
        printf("1. Créer un nouveau compte\n");
        printf("2. Créer une nouvelle élection\n");
        printf("3. Mise à jour des informations des candidats\n");
        printf("4. Afficher et gérer les élections\n");
        printf("5. Afficher le résultat de l'élection\n");
        printf("6. Afficher la liste des votes\n");
        printf("7. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // Créer un nouveau compte (admin ou candidat)
                printf("Choisissez le type de compte (1 pour admin, 2 pour candidat): ");
                int typeCompte;
                scanf("%d", &typeCompte);
                if (typeCompte == 1) {
                    admin = creerAdmin();
                } else if (typeCompte == 2 ) {
                    candidat= creercandidat();
                } else {
                    printf("Nombre maximum d'élections atteint.\n");
                }
                break;
            case 2:
                // Créer une nouvelle élection
                if (nbElections < MAX_ELECTIONS) {
                    creerElection(elections, &nbElections);
                } else {
                    printf("Nombre maximum d'élections atteint.\n");
                }
                break;
            case 3:
                // Mise à jour des informations des candidats
                // Supposons que vous souhaitez mettre à jour le premier candidat de la première élection
                if (nbElections > 0 && elections[0].nbCandidats > 0) {
                    miseAJourCandidat(&elections[0].candidats[0]);
                    printf("Informations du candidat mises à jour avec succès.\n");
                } else {
                    printf("Aucune élection ou candidat pour la mise à jour.\n");
                }
                break;
            case 4:
                // Afficher et gérer les élections
                if (nbElections > 0) {
                    // Supposons que vous souhaitez gérer la première élection
                    gererElection(&elections[0]);
                } else {
                    printf("Aucune élection à gérer.\n");
                }
                break;
            case 5:
                // Afficher le résultat de l'élection
                if (nbElections > 0) {
                    // Supposons que vous souhaitez afficher le résultat de la première élection
                    afficherResultatElection(&elections[0]);
                } else {
                    printf("Aucune élection pour afficher les résultats.\n");
                }
                break;
            case 6:
                // Afficher la liste des votes
                if (nbElections > 0) {
                    // Supposons que vous souhaitez afficher la liste des votes de la première élection
                    afficherListeVotes(&elections[0]);
                } else {
                    printf("Aucune élection pour afficher la liste des votes.\n");
                }
                break;
            case 7:
                printf("Au revoir!\n");
                break;
            default:
                printf("Option invalide. Veuillez entrer un nombre entre 1 et 7.\n");
        }
    } while (choix != 7);

    return 0;
}
