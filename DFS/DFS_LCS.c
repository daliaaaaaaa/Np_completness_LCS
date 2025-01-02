#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "DFS_LCS.h"

char maxLCS[MAX_LEN];
int maxLength = 0;

void stringCopy(char *dest, char *src)
{
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void findLCS(char *str1, char *str2, int i, int j, char *currentLCS, int currentLength)
{
    if (i == strlen(str1) || j == strlen(str2))
    {
        if (currentLength > maxLength)
        {
            maxLength = currentLength;
            stringCopy(maxLCS, currentLCS);
        }
        return;
    }
    if (str1[i] == str2[j])
    {
        currentLCS[currentLength] = str1[i];
        currentLCS[currentLength + 1] = '\0';
        findLCS(str1, str2, i + 1, j + 1, currentLCS, currentLength + 1);
    }
    findLCS(str1, str2, i + 1, j, currentLCS, currentLength);
    findLCS(str1, str2, i, j + 1, currentLCS, currentLength);
}

void generateRandomString(char *str, int length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; i++)
    {
        int key = rand() % (sizeof(charset) - 1);
        str[i] = charset[key];
    }
    str[length] = '\0';
}

void performanceTest()
{
    FILE *fp;
    clock_t start, end;
    double cpu_time_used;
    char str1[MAX_LEN], str2[MAX_LEN];
    char currentLCS[MAX_LEN] = "";

    fp = fopen("DFS_LCS_performance.csv", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "String Length,Execution Time (seconds)\n");

    for (int len = 4; len <= 20; len += 2)
    {
        generateRandomString(str1, len);
        generateRandomString(str2, len);
        maxLCS[0] = '\0';
        maxLength = 0;
        start = clock();
        findLCS(str1, str2, 0, 0, currentLCS, 0);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Testing length %d: %.6f seconds\n", len, cpu_time_used);
        fprintf(fp, "%d,%.6f\n", len, cpu_time_used);
    }

    fclose(fp);
    printf("\nResults saved to lcs_performance.csv\n");
}

void DFS_LCS()
{
    char str1[MAX_LEN], str2[MAX_LEN];
    char currentLCS[MAX_LEN] = "";
    int choice, length;

    srand(time(NULL));

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
            printf("Enter length for first random string: ");
            scanf("%d", &length);
            if (length >= MAX_LEN)
            {
                printf("Length too large. Maximum allowed: %d\n", MAX_LEN - 1);
                break;
            }
            generateRandomString(str1, length);

            printf("Enter length for second random string: ");
            scanf("%d", &length);
            if (length >= MAX_LEN)
            {
                printf("Length too large. Maximum allowed: %d\n", MAX_LEN - 1);
                break;
            }
            generateRandomString(str2, length);
            if (length >= MAX_LEN)
            {
                printf("Length too large. Maximum allowed: %d\n", MAX_LEN - 1);
                break;
            }

            printf("Generated string 1: %s\n", str1);
            printf("Generated string 2: %s\n", str2);
            break;

        case 2:
            printf("Enter first string: ");
            scanf("%s", str1);
            printf("Enter second string: ");
            scanf("%s", str2);
            break;

        case 3:
            performanceTest();
            break;

        case 4:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
            continue;
        }

        if (choice != 3 && choice != 4)
        {
            maxLCS[0] = '\0';
            maxLength = 0;
            findLCS(str1, str2, 0, 0, currentLCS, 0);
            printf("Longest Common Subsequence: %s\n", maxLCS);
            printf("Length of LCS: %d\n", maxLength);
        }
    }
}
