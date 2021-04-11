#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(nullptr);
    cout.tie(nullptr);
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
        matrix[fir - 1][sec - 1] = 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << '\t';
        }
        cout << '\n';
    }
    return 0;
}