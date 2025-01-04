#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "BFS_LCS.h"

// Fonction pour initialiser une queue
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

// Fonction pour ajouter un état à la queue
void enqueue(Queue *q, State state) {
    Bfs_Node *temp = (Bfs_Node *)malloc(sizeof(Bfs_Node));
    temp->state = state;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// Fonction pour retirer un état de la queue
State dequeue(Queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        exit(1);
    }
    Bfs_Node *temp = q->front;
    State state = temp->state;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return state;
}

// Fonction pour résoudre LCS avec BFS et récupérer la LCS elle-même
char* LCS_BFS(char *X, char *Y, char *result) {
    int m = strlen(X);
    int n = strlen(Y);

    // Initialiser la queue et la table de visite
    Queue q;
    initQueue(&q);

    bool visited[m + 1][n + 1];
    memset(visited, 0, sizeof(visited));

    // Ajouter le point de départ à la queue
    State start = {0, 0, "", 0};
    enqueue(&q, start);
    visited[0][0] = 1;

    char longest_lcs[100] = ""; // LCS finale
    int max_len = 0;

    // BFS
    while (q.front != NULL) {
        State current = dequeue(&q);

        // Si les caractères correspondent, ajouter à la LCS
        if (current.i < m && current.j < n && X[current.i] == Y[current.j]) {
            State next = current;
            next.i++;
            next.j++;
            next.lcs[next.len] = X[current.i];
            next.len++;
            next.lcs[next.len] = '\0';

            if (!visited[next.i][next.j]) {
                visited[next.i][next.j] = 1;
                enqueue(&q, next);

                if (next.len > max_len) {
                    max_len = next.len;
                    strcpy(longest_lcs, next.lcs);
                }
            }
        }

        // Avancer sans correspondance
        if (current.i + 1 <= m && !visited[current.i + 1][current.j]) {
            State next = current;
            next.i++;
            visited[next.i][next.j] = 1;
            enqueue(&q, next);
        }
        if (current.j + 1 <= n && !visited[current.i][current.j + 1]) {
            State next = current;
            next.j++;
            visited[next.i][next.j] = 1;
            enqueue(&q, next);
        }
    }

    strcpy(result, longest_lcs);
    return result;
}

// Génère une chaîne aléatoire de taille donnée
void generate_Random_String(char *str, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; i++)
    {
        int key = rand() % (sizeof(charset) - 1);
        str[i] = charset[key];
    }
    str[length] = '\0';
}

void calculateComplexity(const char *filename, int maxLength, int step) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    fprintf(file, "Taille,Temps (s)\n");

    char X[1000];
    char Y[1000];
    char result[1000];

    for (int len = step; len <= maxLength; len += step) {
        generate_Random_String(X, len);
        generate_Random_String(Y, len);

        clock_t start = clock();
        LCS_BFS(X, Y, result); // Utiliser l'algorithme BFS LCS
        clock_t end = clock();

        double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) ; 
        fprintf(file, "%d,%.3f\n", len, time_taken);

       
    }

    fclose(file);
}

void BFS_LCS_Menu() {
    char str1[1000], str2[1000], currentLCS[1000];
    int choice, length;

    srand(time(NULL)); // Initialiser la graine aléatoire

    do {
        printf("\nMenu Of Solving LCS using BFS:\n");
        printf("1. Test with random strings\n");
        printf("2. Input custom strings\n");
        printf("3. Run performance test\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: // Générer des chaînes aléatoires
            printf("Enter length for first random string: ");
            scanf("%d", &length);
            if (length >= sizeof(str1)) {
                printf("Length too large. Maximum allowed: %d\n", (int)(sizeof(str1) - 1));
                break;
            }
            generate_Random_String(str1, length);

            printf("Enter length for second random string: ");
            scanf("%d", &length);
            if (length >= sizeof(str2)) {
                printf("Length too large. Maximum allowed: %d\n", (int)(sizeof(str2) - 1));
                break;
            }
            generate_Random_String(str2, length);

            printf("Generated string 1: %s\n", str1);
            printf("Generated string 2: %s\n", str2);
            break;

        case 2: // Saisir des chaînes personnalisées
            printf("Enter first string: ");
            scanf("%s", str1);
            printf("Enter second string: ");
            scanf("%s", str2);
            break;

        case 3: // Tester les performances
            calculateComplexity("performance_bfs.csv", 700, 50);
            printf("Performance test results saved to performance_bfs.csv.\n");
            continue;

        case 4: // Quitter
            printf("Exiting program.\n");
            break;

        default: // Choix invalide
            printf("Invalid choice! Please try again.\n");
            continue;
        }

        if (choice == 1 || choice == 2) {
            currentLCS[0] = '\0'; // Réinitialiser LCS
            LCS_BFS(str1, str2, currentLCS);
            printf("Longest Common Subsequence: %s\n", currentLCS);
            printf("Length of LCS: %d\n", (int)strlen(currentLCS));
        }

    } while (choice != 4);
}


