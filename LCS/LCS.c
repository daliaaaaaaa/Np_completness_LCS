#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "LCS.h"

// LCS naive
int lcs_naive(const char *X, const char *Y, int m, int n) {
    if (m == 0 || n == 0)
        return 0;
    if (X[m - 1] == Y[n - 1])
        return 1 + lcs_naive(X, Y, m - 1, n - 1);
    else
        return (lcs_naive(X, Y, m, n - 1) > lcs_naive(X, Y, m - 1, n)) ? lcs_naive(X, Y, m, n - 1) : lcs_naive(X, Y, m - 1, n);
}

// Fonction pour récupérer la LCS à partir de la table de programmation dynamique
char* get_lcs(const char *X, const char *Y, int m, int n) {

    int **L = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++)
        L[i] = (int *)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }
    int index = L[m][n];
    char *lcs = (char *)malloc((index + 1) * sizeof(char));
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    for (int i = 0; i <= m; i++)
        free(L[i]);
    free(L);

    return lcs;
}

// Fonction pour calculer LCS 
int lcs_dp(const char *X, const char *Y, int m, int n) {
    int **L = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++)
        L[i] = (int *)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }

    int result = L[m][n];
    for (int i = 0; i <= m; i++)
        free(L[i]);
    free(L);

    return result;
}

// Tests pour des tailles différentes
void complexite_lcs() {
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires
    FILE *f = fopen("lcs_results.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(f, "i,Length_LCS,time\n");
    for (int i = 10; i <= 1000000; i += 10) {
        char *X = (char *)malloc((i / 2 + 1) * sizeof(char));
        char *Y = (char *)malloc((i + 1) * sizeof(char));

        for (int k = 0; k < i / 2; k++) {
            X[k] = 'A' + (rand() % 26);
        }
        X[i / 2] = '\0';

        for (int k = 0; k < i; k++) {
            Y[k] = 'A' + (rand() % 26);
        }
        Y[i] = '\0';

        clock_t start = clock();
        int temp = lcs_dp(X, Y, i / 2, i);
        clock_t end = clock();

        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        fprintf(f, "%d,%d,%f\n", i, temp, cpu_time_used);

        printf("Length %d: LCS = %d, Time = %f seconds\n", i, temp, cpu_time_used);

        free(X);
        free(Y);
    }
    fclose(f);
}

// Menu principal
void display_menu_lcs() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. LCS naive\n");
        printf("2. LCS dynamique\n");
        printf("3. Essaies LCS dynamique pour complexite experimentale\n");
        printf("4. Exit\n");
        printf("Entrer un choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char X[1000], Y[1000];
                printf("Enter the first string: ");
                scanf("%s", X);

                printf("Enter the second string: ");
                scanf("%s", Y);

                int m = strlen(X);
                int n = strlen(Y);

                printf("\nFirst string (X): %s\n", X);
                printf("Second string (Y): %s\n", Y);
                printf("LCS: %d\n", lcs_naive(X, Y, m, n));
                break;
            }
            case 2: {
                char X[1000], Y[1000];
                char *r;
                printf("Enter the first string: ");
                scanf("%s", X);

                printf("Enter the second string: ");
                scanf("%s", Y);

                int m = strlen(X);
                int n = strlen(Y);

                printf("\nFirst string (X): %s\n", X);
                printf("Second string (Y): %s\n", Y);
                
                r = get_lcs(X, Y, m, n);
                printf("\nLCS: %s\n", r);
                break;
            }
            case 3:
                complexite_lcs();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

int main() {
    display_menu_lcs();
    return 0;
}
