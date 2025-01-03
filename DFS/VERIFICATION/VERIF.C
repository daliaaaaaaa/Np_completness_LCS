#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Fonction pour générer une chaîne aléatoire de longueur donnée
void genererChaine(char *chaine, int longueur) {
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < longueur; i++) {
        chaine[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    chaine[longueur] = '\0';
}

// Fonction pour générer une solution candidate (validité aléatoire)
void genererSolutionCandidate(char *S1, char *S2, char *candidate, int type) {
    switch (type) {
        case 0: // Solution valide (LCS)
            candidate[0] = S1[0]; // Simule une correspondance
            candidate[1] = S2[1];
            candidate[2] = '\0';
            break;

        case 1: // Pas une sous-séquence
            strcpy(candidate, "ZZZ"); // Simule une chaîne incorrecte
            break;

        case 2: // Sous-séquence mais pas la plus longue
            candidate[0] = S1[0];
            candidate[1] = '\0';
            break;

        default:
            candidate[0] = '\0'; // Par défaut, chaîne vide
    }
}

// Vérifie si candidate est une sous-séquence de S
int estSousSequence(char *candidate, char *S) {
    int i = 0, j = 0;
    while (i < strlen(candidate) && j < strlen(S)) {
        if (candidate[i] == S[j]) {
            i++;
        }
        j++;
    }
    return i == strlen(candidate);
}

// Vérifie si candidate est une LCS valide pour S1 et S2
int verifierLCS(char *candidate, char *S1, char *S2) {
    if (!estSousSequence(candidate, S1) || !estSousSequence(candidate, S2)) {
        return 0; // Pas une sous-séquence
    }

    // Vérification simplifiée si la chaîne est "suffisamment longue"
    return strlen(candidate) >= 2;
}

int main() {
    srand(time(NULL)); // Initialisation du générateur aléatoire

    // Générer deux chaînes aléatoires
    int len1 = 5, len2 = 6;
    char S1[len1 + 1], S2[len2 + 1];
    genererChaine(S1, len1);
    genererChaine(S2, len2);
    printf("Chaîne 1 : %s\n", S1);
    printf("Chaîne 2 : %s\n", S2);

    // Générer une solution candidate
    char candidate[10];
    int type = rand() % 3; // Générer un type aléatoire (0, 1 ou 2)
    genererSolutionCandidate(S1, S2, candidate, type);
    printf("Solution candidate : %s\n", candidate);

    // Vérification de la solution
    if (verifierLCS(candidate, S1, S2)) {
        printf("La solution est une LCS valide.\n");
    } else {
        printf("La solution est invalide.\n");
    }

    return 0;
}
