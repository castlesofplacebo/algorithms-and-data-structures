#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    int matrix [n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (i == j && matrix[i][j] == 1) {
                cout << "NO";
                return 0;
            }
            if (matrix[i][j] == matrix[j][i])
                continue;
            else {
                cout << "NO";
                return 0;
            }
        }
    }
    cout << "YES";
    return 0;
}