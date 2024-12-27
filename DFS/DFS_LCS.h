#ifndef DFS_LCS_H
#define DFS_LCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants
#define MAX_LEN 100

// Function prototypes
void generateRandomString(char *str, int length);
void findLCS(char *str1, char *str2, int i, int j, char *currentLCS, int currentLength);
void performanceTest(void);
void DFS_LCS();


#endif // DFS_LCS_H