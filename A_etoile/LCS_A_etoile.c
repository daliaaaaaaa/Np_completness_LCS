#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "LCS_A_etoile.h"

// Initialize priority queue
void initPriorityQueue(PriorityQueue *pq)
{
    pq->front = NULL;
}

// Insert into priority queue (ordered by f_score)
void insert(PriorityQueue *pq, Node *node)
{
    if (pq->front == NULL || node->f_score > pq->front->f_score)
    {
        node->next = pq->front;
        pq->front = node;
        return;
    }

    Node *current = pq->front;
    while (current->next != NULL && current->next->f_score >= node->f_score)
    {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
}

// Remove and return the node with highest f_score
Node *pop(PriorityQueue *pq)
{
    if (pq->front == NULL)
        return NULL;

    Node *node = pq->front;
    pq->front = pq->front->next;
    node->next = NULL;
    return node;
}

// Calculate heuristic: remaining possible matches
int calculateHeuristic(char *X, char *Y, int i, int j, int m, int n)
{
    int remaining_chars = 0;
    int min_remaining = (m - i) < (n - j) ? (m - i) : (n - j);
    return min_remaining;
}

// Create a new node
Node *createNode(int i, int j, int length, char *sequence, int f, int g, int h)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->i = i;
    node->j = j;
    node->length = length;
    node->sequence = (char *)malloc((length + 1) * sizeof(char));
    strcpy(node->sequence, sequence);
    node->f_score = f;
    node->g_score = g;
    node->h_score = h;
    node->next = NULL;
    return node;
}

// Main A* search function for LCS
char *findLCSAStar(char *X, char *Y)
{
    int m = strlen(X);
    int n = strlen(Y);

    PriorityQueue pq;
    initPriorityQueue(&pq);

    // Create initial node
    char *initial_seq = (char *)malloc(sizeof(char));
    initial_seq[0] = '\0';
    int h = calculateHeuristic(X, Y, 0, 0, m, n);
    Node *start = createNode(0, 0, 0, initial_seq, h, 0, h);
    free(initial_seq);

    insert(&pq, start);
    char *best_sequence = NULL;
    int best_length = 0;

    // A* search
    while (pq.front != NULL)
    {
        Node *current = pop(&pq);

        // Check if we've reached the end of either string
        if (current->i == m || current->j == n)
        {
            if (current->length > best_length)
            {
                best_length = current->length;
                if (best_sequence != NULL)
                    free(best_sequence);
                best_sequence = (char *)malloc((best_length + 1) * sizeof(char));
                strcpy(best_sequence, current->sequence);
            }
            free(current->sequence);
            free(current);
            continue;
        }

        // Try matching current characters
        if (X[current->i] == Y[current->j])
        {
            char *new_seq = (char *)malloc((current->length + 2) * sizeof(char));
            strcpy(new_seq, current->sequence);
            new_seq[current->length] = X[current->i];
            new_seq[current->length + 1] = '\0';

            int new_g = current->length + 1;
            int new_h = calculateHeuristic(X, Y, current->i + 1, current->j + 1, m, n);

            Node *match_node = createNode(current->i + 1, current->j + 1,
                                          current->length + 1, new_seq,
                                          new_g + new_h, new_g, new_h);
            free(new_seq);
            insert(&pq, match_node);
        }

        // Try skipping character in X
        int skip_x_h = calculateHeuristic(X, Y, current->i + 1, current->j, m, n);
        Node *skip_x = createNode(current->i + 1, current->j,
                                  current->length, current->sequence,
                                  current->g_score + skip_x_h,
                                  current->g_score, skip_x_h);
        insert(&pq, skip_x);

        // Try skipping character in Y
        int skip_y_h = calculateHeuristic(X, Y, current->i, current->j + 1, m, n);
        Node *skip_y = createNode(current->i, current->j + 1,
                                  current->length, current->sequence,
                                  current->g_score + skip_y_h,
                                  current->g_score, skip_y_h);
        insert(&pq, skip_y);

        free(current->sequence);
        free(current);
    }

    return best_sequence;
}
void generateRandomStringA(char *str, int length)
{
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length; i++)
    {
        str[i] = charset[rand() % 26];
    }
    str[length] = '\0';
}

void testWithRandomStrings()
{
    srand(time(NULL));
    int length1, length2;
    char str1[100], str2[100];

    printf("Enter length of first string: ");
    scanf("%d", &length1);
    printf("Enter length of second string: ");
    scanf("%d", &length2);

    generateRandomStringA(str1, length1);
    generateRandomStringA(str2, length2);

    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);

    char *result = findLCSAStar(str1, str2);
    printf("LCS: %s\n", result);
    free(result);
}

void inputCustomStrings()
{
    char str1[100], str2[100];
    printf("Enter first string: ");
    scanf("%s", str1);
    printf("Enter second string: ");
    scanf("%s", str2);

    char *result = findLCSAStar(str1, str2);
    printf("LCS: %s\n", result);
    free(result);
}

void runPerformanceTest()
{
    FILE *csv_file = fopen("A_etoile_LCS_performance.csv", "w");
    if (csv_file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    // Write CSV header
    fprintf(csv_file, "String Length,Time (seconds)\n");

    // Test different string lengths
    char str1[100], str2[100];

    for (int i = 4; i <= 20; i += 1)
    {

        generateRandomStringA(str1, i);
        generateRandomStringA(str2, i);

        clock_t start = clock();
        char *result = findLCSAStar(str1, str2);
        clock_t end = clock();

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        // Write to CSV
        fprintf(csv_file, "%d,%f\n", i, time_spent);

        free(result);
    }

    fclose(csv_file);
    printf("Performance results written to lcs_performance_results.csv\n");
}

void LCS_A_STAR()
{
    int choice = 0;
    while (choice != 4)
    {
        printf("\nMenu Of solving LCS using DFS:\n");
        printf("1. Test with random strings\n");
        printf("2. Input custom strings\n");
        printf("3. Run performance test\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            testWithRandomStrings();
            break;
        case 2:
            inputCustomStrings();
            break;
        case 3:
            runPerformanceTest();
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    }
}