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
char *generate_random_string(int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *random_string = (char *)malloc((length + 1) * sizeof(char));
    int charset_size = sizeof(charset) - 1;

    for (int i = 0; i < length; i++) {
        random_string[i] = charset[rand() % charset_size];
    }
    random_string[length] = '\0';
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

// Fonction pour enregistrer les résultats dans un fichier CSV
void save_results_to_csv(const char *filename, int lcs_length, double gen_time, double lcs_time) {
    FILE *file = fopen(filename, "a");  // Ouvre le fichier en mode ajout
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier CSV.\n");
        return;
    }
    
    fprintf(file, "%d,%lf,%lf\n", lcs_length, gen_time, lcs_time);
    fclose(file);
}

// Programme principal
int main() {
    srand(time(NULL));

    // Fichier CSV pour enregistrer les résultats
    const char *filename = "verification_results.csv";
    
    // Ouvrir le fichier pour ajouter les en-têtes si vide
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "LCS_Length,Generation_Time,LCS_Calculation_Time\n");
        fclose(file);
    }

    int sizes[] = {0 , 10 , 20 , 50 , 77 , 100 , 200 , 300 , 350 , 400 , 500 , 600 , 650 , 700};  // Les tailles à tester
    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {  // Nous avons 7 tailles dans le tableau
        int size = sizes[i];

        // Générer des chaînes S1 et S2 de taille `size`
        char *S1 = generate_random_string(size);
        char *S2 = generate_random_string(size);

        clock_t start, end;
        
        // Générer une chaîne aléatoire
        start = clock();
        char *random_string = generate_random_string(size);
        end = clock();
        double gen_time = (double)(end - start) / CLOCKS_PER_SEC;

        // Calcul de la longueur de la LCS
        start = clock();
        int lcs_length = compute_lcs_length(S1, S2);
        end = clock();
        double lcs_time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("Pour les tailles %d, LCS : %d, Temps de génération : %lf s, Temps de calcul LCS : %lf s\n",
               size, lcs_length, gen_time, lcs_time);

        // Enregistrer les résultats dans le fichier CSV
        save_results_to_csv(filename, lcs_length, gen_time, lcs_time);

        // Libérer la mémoire allouée
        free(random_string);
        free(S1);
        free(S2);
    }

    return 0;
}
