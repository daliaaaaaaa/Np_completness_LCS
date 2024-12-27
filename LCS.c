#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// Function to find the length of the longest common subsequence
int lcs(const char *X, const char *Y, int m, int n) {
    int L[m + 1][n + 1];
    int i, j;

    // Building the L[m+1][n+1] table in bottom-up fashion
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }

    // L[m][n] contains the length of LCS for X[0..m-1], Y[0..n-1]
    return L[m][n];
}

// Test for different lengths
void complexite_lcs() {
    int temp;
    FILE *f = fopen("lcs_results.csv", "w");
    fprintf(f, "i,Length_LCS,time\n");
    for(int i = 10; i < 1000000; i *= 10) {
        char *X = (char *)malloc((i / 2 + 1) * sizeof(char));
        char *Y = (char *)malloc((i + 1) * sizeof(char));

        // random string of length i/2
        for (int k = 0; k < i / 2; k++) {
            X[k] = 'A' + (rand() % 26);
        }
        X[i / 2] = '\0';

        // random string of length i
        for (int k = 0; k < i; k++) {
            Y[k] = 'A' + (rand() % 26);
        }
        Y[i] = '\0';

        int m = strlen(X);
        int n = strlen(Y);

        if (f == NULL) {
            printf("Error opening file!\n");
            free(X);
            free(Y);
            return;
        }
        
        clock_t start, end;
        double cpu_time_used;

        start = clock();
        temp = lcs(X, Y, m, n);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(f, "%d,%d,%f\n", i, temp, cpu_time_used);

        free(X);
        free(Y);
    }
    fclose(f);
}

int test_lcs() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    int m = strlen(X);
    int n = strlen(Y);

    printf("X: %s, Length: %d\n", X, m);
    printf("Y: %s, Length: %d\n", Y, n);

    printf("Length of LCS is %d\n", lcs(X, Y, m, n));

    return 0;
}

void display_menu_lcs() {
    int choice;
    do {
        printf("Menu:\n");
        printf("1. LCS dynamique\n");
        printf("2. Essaies LCS dynamique pour complexité experimentale\n");
        printf("3. Exit\n");
        printf("Entrer un choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                test_lcs();
                break;
            case 2:
                complexite_lcs();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

int main() {
    display_menu_lcs();
    return 0;
}
