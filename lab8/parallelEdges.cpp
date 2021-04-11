#include <iostream>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    int matrix [n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = 0;
        }
    }
    int fir, sec;
    for (int i = 0; i < m; ++i) {
        cin >> fir >> sec;
        ++matrix[fir - 1][sec - 1];
        ++matrix[sec - 1][fir - 1];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (matrix[i][j] != 0 && matrix[i][j] != 1) {
                cout << "YES";
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}