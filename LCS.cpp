#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

// Function to find the length of the longest common subsequence
int lcs(const std::string &X, const std::string &Y, int m, int n) {
    std::vector<std::vector<int>> L(m + 1, std::vector<int>(n + 1));
    int i, j;

    // Building the L[m+1][n+1] table in bottom-up fashion
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = std::max(L[i - 1][j], L[i][j - 1]);
        }
    }

    // L[m][n] contains the length of LCS for X[0..m-1], Y[0..n-1]
    return L[m][n];
}

// Test for different lengths
void complexite_lcs() {
    std::srand(std::time(0));
    for(int i = 10; i < 1000000; i *= 10) {
        std::string X(i / 2, ' ');
        std::string Y(i, ' ');

        // random string of length i/2
        for (int k = 0; k < i / 2; k++) {
            X[k] = 'A' + (std::rand() % 26);
        }

        // random string of length i
        for (int k = 0; k < i; k++) {
            Y[k] = 'A' + (std::rand() % 26);
        }

        int m = X.length();
        int n = Y.length();

        std::cout << "For i : " << i << " , Length of LCS is " << lcs(X, Y, m, n) << std::endl;

        std::ofstream file("lcs_cpp_results.csv", std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        file << i << "," << lcs(X, Y, m, n) << std::endl;
    }
}

int test_lcs() {
    std::string X = "AGGTAB";
    std::string Y = "GXTXAYB";

    int m = X.length();
    int n = Y.length();

    std::cout << "X: " << X << ", Length: " << m << std::endl;
    std::cout << "Y: " << Y << ", Length: " << n << std::endl;

    std::cout << "Length of LCS is " << lcs(X, Y, m, n) << std::endl;

    return 0;
}

void display_menu_lcs() {
    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. LCS dynamique\n";
        std::cout << "2. Essaies LCS dynamique pour complexité experimentale\n";
        std::cout << "3. Exit\n";
        std::cout << "Entrer un choix: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                test_lcs();
                break;
            case 2:
                complexite_lcs();
                break;
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

int main() {
    display_menu_lcs();
    return 0;
}
