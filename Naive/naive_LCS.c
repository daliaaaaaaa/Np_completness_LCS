#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "naive_LCS.h"

int max(int x, int y)
{
    return x > y ? x : y;
}

int lcsNaive(char *s1, char *s2, int m, int n, char *lcs_str)
{
    if (m == 0 || n == 0)
        return 0;

    if (s1[m - 1] == s2[n - 1])
    {
        int len = lcsNaive(s1, s2, m - 1, n - 1, lcs_str);
        lcs_str[len] = s1[m - 1];
        return len + 1;
    }
    else

        return max(lcsNaive(s1, s2, m, n - 1, lcs_str), lcsNaive(s1, s2, m - 1, n, lcs_str));
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

    fp = fopen("naive_LCS_performance.csv", "w");
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

        start = clock();
        char lcs_result[MAX_LEN];
        memset(lcs_result, 0, sizeof(lcs_result));
        int result = lcsNaive(str1, str2, len, len, lcs_result);
        end = clock();

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Testing length %d: %.6f seconds\n", len, cpu_time_used);
        fprintf(fp, "%d,%.6f\n", len, cpu_time_used);
    }

    fclose(fp);
    printf("\nResults saved to lcs_performance.csv\n");
}

void naiveLCS()
{
    char str1[MAX_LEN], str2[MAX_LEN];
    int choice, length;

    srand(time(NULL));

    while (1)
    {
        printf("\nMenu Of solving LCS :\n");
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
            return;

        default:
            printf("Invalid choice! Please try again.\n");
            continue;
        }

        if (choice != 3 && choice != 4)
        {
            char lcs_result[MAX_LEN];
            memset(lcs_result, 0, sizeof(lcs_result));
            int result = lcsNaive(str1, str2, strlen(str1), strlen(str2), lcs_result);
            printf("Length of Longest Common Subsequence: %d\n", result);
            printf("Longest Common Subsequence: %s\n", lcs_result);
        }
    }
}