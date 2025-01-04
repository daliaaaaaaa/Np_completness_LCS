#ifndef NAIVE_LCS_H
#define NAIVE_LCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants
#define MAX_LEN 100

// Function prototypes
void generateRandomString(char *str, int length);
int lcsNaive(char *s1, char *s2, int m, int n, char *lcs_str);
void performanceTest(void);
void naiveLCS();

#endif // DFS_LCS_H