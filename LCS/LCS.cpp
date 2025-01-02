#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Function to calculate LCS using dynamic programming
int lcs_dp(const string &X, const string &Y, int m, int n) {
    int **L = new int*[m + 1];
    for (int i = 0; i <= m; i++) {
        L[i] = new int[n + 1]();
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    int result = L[m][n];
    
    // Clean up the dynamically allocated memory
    for (int i = 0; i <= m; i++) {
        delete[] L[i];
    }
    delete[] L;

    return result;
}

// Test for different lengths
void complexite_lcs() {
    srand(time(0)); // Initialize random number generator
    ofstream f("lcs_cpp_results.csv");
    if (!f) {
        cout << "Error opening file!" << endl;
        return;
    }

    f << "i,Length_LCS,time" << endl;
    for (int i = 10; i <= 29170; i += 10) {
        string X(i / 2, ' '), Y(i, ' ');

        for (int k = 0; k < i / 2; k++) {
            X[k] = 'A' + (rand() % 26);
        }

        for (int k = 0; k < i; k++) {
            Y[k] = 'A' + (rand() % 26);
        }

        clock_t start = clock();
        int temp = lcs_dp(X, Y, i / 2, i);
        clock_t end = clock();

        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        f << i << "," << temp << "," << cpu_time_used << endl;

        cout << "Length " << i << ": LCS = " << temp << ", Time = " << cpu_time_used << " seconds" << endl;
    }

    f.close();
}

// Main menu function
void display_menu_lcs() {
    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. LCS dynamique" << endl;
        cout << "2. Essaies LCS dynamique pour complexite experimentale" << endl;
        cout << "3. Exit" << endl;
        cout << "Entrer un choix: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string X, Y;
                cout << "Enter the first string: ";
                cin >> X;

                cout << "Enter the second string: ";
                cin >> Y;

                int m = X.length();
                int n = Y.length();

                cout << "\nFirst string (X): " << X << endl;
                cout << "Second string (Y): " << Y << endl;

                int length = lcs_dp(X, Y, m, n);
                cout << "\nLength of LCS: " << length << endl;
                break;
            }
            case 2:
                complexite_lcs();
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}

int main() {
    display_menu_lcs();
    return 0;
}
