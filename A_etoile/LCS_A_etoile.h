#ifndef LCS_A_ETOILE_H
#define LCS_A_ETOILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure for a node in the search space
typedef struct Node
{
    int i;             // Position in first string
    int j;             // Position in second string
    int length;        // Length of current LCS
    char *sequence;    // Current LCS sequence
    int f_score;       // f = g + h (f score for A*)
    int g_score;       // g = current length (g score for A*)
    int h_score;       // h = heuristic estimate
    struct Node *next; // For priority queue
} Node;

// Priority Queue structure
typedef struct
{
    Node *front;
} PriorityQueue;
void initPriorityQueue(PriorityQueue *pq);
void insert(PriorityQueue *pq, Node *node);
Node *pop(PriorityQueue *pq);
int calculateHeuristic(char *X, char *Y, int i, int j, int m, int n);
Node *createNode(int i, int j, int length, char *sequence, int f, int g, int h);

char *findLCSAStar(char *X, char *Y);
void generateRandomStringA(char *str, int length);
void testWithRandomStrings();
void inputCustomStrings();
void runPerformanceTest();

void LCS_A_STAR();

#endif // LCS_A_ETOILE_H