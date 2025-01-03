#ifndef LCS_BFS_UTIL_H
#define LCS_BFS_UTIL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure pour représenter un état dans la recherche BFS
typedef struct {
    int i, j; // i et j représentent les indices dans X et Y
    char lcs[100]; // La LCS courante 
    int len;       // Longueur de la LCS jusqu'à cet état
} State;

// Structure pour une file
typedef struct Bfs_Node {
    State state;
    struct Bfs_Node *next;
} Bfs_Node;

typedef struct {
    Bfs_Node *front, *rear;
} Queue;

// Prototypes des fonctions
void initQueue(Queue *q);
void enqueue(Queue *q, State state);
State dequeue(Queue *q);
char* LCS_BFS(char *X, char *Y, char *result);
void generate_Random_String(char *str, int length);
void calculateComplexity(const char *filename, int maxLength, int step);
void BFS_LCS_Menu();
#endif
