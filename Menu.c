#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DFS\DFS_LCS.h"
#include "LCS\LCS.h"

void DFS_LCS();

int main()
{
    int choice = -1;
    while (choice != 0)
    {
        printf("\nChoose an LCS method:\n");
        printf("1. Dynamic Programming\n");
        printf("2. DFS\n");
        printf("3. BFS\n");
        printf("4. Verification\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display_menu_lcs();
            break;
        case 2:
            printf("You chose DFS method.\n");
            DFS_LCS();

        case 3:
            // ...call BFS LCS function here...

        case 4:
            // ...call Verfication LCS function here...

        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
