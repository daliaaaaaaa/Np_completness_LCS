#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Fonction pour vérifier si `subseq` est une sous-séquence de `str`
bool is_subsequence(const char *subseq, const char *str) {
    int i = 0, j = 0;
    while (i < strlen(subseq) && j < strlen(str)) {
        if (subseq[i] == str[j]) {
            i++;
        }
        j++;
    }
    return i == strlen(subseq);
}

// Fonction pour calculer la longueur de la LCS entre S1 et S2
int compute_lcs_length(const char *S1, const char *S2) {
    int len1 = strlen(S1);
    int len2 = strlen(S2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (S1[i - 1] == S2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    return dp[len1][len2];
}

// Fonction pour générer une chaîne aléatoire
char *generate_random_string(const char *S1, const char *S2) {
    int max_len = rand() % (strlen(S1) + strlen(S2)) + 1;
    char *random_string = (char *)malloc((max_len + 1) * sizeof(char));

    for (int i = 0; i < max_len; i++) {
        if (rand() % 2 == 0 && strlen(S1) > 0) {
            random_string[i] = S1[rand() % strlen(S1)];
        } else if (strlen(S2) > 0) {
            random_string[i] = S2[rand() % strlen(S2)];
        } else {
            random_string[i] = ' ';
        }
    }
    random_string[max_len] = '\0';
    return random_string;
}

// Fonction pour générer une sous-séquence aléatoire valide de S1 et S2
char *generate_random_valid_subsequence(const char *S1, const char *S2) {
    int len1 = strlen(S1);
    int len2 = strlen(S2);
    char *result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
    result[0] = '\0';

    int i = 0, j = 0, k = 0;
    while (i < len1 && j < len2) {
        if (S1[i] == S2[j] && rand() % 2 == 0) { // Aléatoirement inclure un caractère commun
            result[k++] = S1[i];
        }
        if (rand() % 2 == 0) i++;
        else j++;
    }
    result[k] = '\0';
    return result;
}

// Programme principal
int main() {
    srand(time(NULL));

    char S1[100], S2[100], candidate[100];

    printf("Entrez la première chaîne S1 : ");
    scanf("%s", S1);
    printf("Entrez la deuxième chaîne S2 : ");
    scanf("%s", S2);

    printf("\n1. Générer une chaîne aléatoire et analyser\n2. Valider une solution\nChoix : ");
    int choice;
    scanf("%d", &choice);

    clock_t start, end;

    if (choice == 1) {
        start = clock();
        char *random_string = generate_random_string(S1, S2);
        end = clock();
        printf("Chaîne générée : %s\n", random_string);
        printf("Temps de génération de la chaîne aléatoire : %lf secondes\n", (double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        int lcs_length = compute_lcs_length(S1, S2);
        end = clock();
        printf("Temps de calcul de la longueur de la LCS : %lf secondes\n", (double)(end - start) / CLOCKS_PER_SEC);

        // Si la chaîne générée est une sous-séquence et qu'elle a la même longueur que la LCS
        if (is_subsequence(random_string, S1) && is_subsequence(random_string, S2)) {
            if (strlen(random_string) == lcs_length) {
                printf("La chaîne générée est la LCS valide.\n");
            } else {
                printf("La chaîne générée est une sous-séquence valide mais pas la plus longue.\n");
            }
        } else {
            printf("La chaîne générée n'est pas une sous-séquence de S1 ou S2.\n");
        }

        free(random_string);
    } else if (choice == 2) {
        printf("Entrez la chaîne candidate à valider : ");
        scanf("%s", candidate);

        start = clock();
        int lcs_length = compute_lcs_length(S1, S2);
        end = clock();
        printf("Temps de calcul de la longueur de la LCS : %lf secondes\n", (double)(end - start) / CLOCKS_PER_SEC);

        // Validation de la solution candidate
        start = clock();
        if (is_subsequence(candidate, S1) && is_subsequence(candidate, S2)) {
            if (strlen(candidate) == lcs_length) {
                printf("La chaîne candidate est la LCS valide.\n");
            } else {
                printf("La chaîne candidate est une sous-séquence valide mais pas la plus longue.\n");
            }
        } else {
            printf("La chaîne candidate n'est pas une sous-séquence de S1 ou S2.\n");
        }
        end = clock();
        printf("Temps de validation de la solution candidate : %lf secondes\n", (double)(end - start) / CLOCKS_PER_SEC);
    } else {
        printf("Choix invalide.\n");
    }

    return 0;
}
