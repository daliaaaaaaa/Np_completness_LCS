#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DFS\DFS_LCS.h"
#include "LCS\LCS.h"
#include "BFS_LCS\BFS_LCS.h"
#include "A_etoile\LCS_A_etoile.h"

void DFS_LCS();
void LCS_A_STAR();
void BFS_LCS_Menu();
int main()
{
    int choice = -1;
    while (choice != 0)
    {
        printf("\nChoose an LCS solving method:\n");
        printf("1. Dynamic Programming\n");
        printf("2. DFS\n");
        printf("3. BFS\n");
        printf("4. A*\n");
        printf("5. Verification\n");
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
            break;
        case 3:
          BFS_LCS_Menu();
        break;
        case 4:
            LCS_A_STAR();
            break;
        case 5:
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