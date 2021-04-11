#include <iostream>
using namespace std;

int main() {
    freopen("pathsg.in", "r", stdin);
    freopen("pathsg.out", "w", stdout);
    long long n, m;
    cin >> n >> m;

    long long array[n][n];
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            array[i][j] = INT32_MAX;
        }
    }

    for (long long i = 0; i < n; ++i) {
        array[i][i] = 0;
    }

    long long first, second, wei;
    for (long long i = 0; i < m; ++i) {
        cin >> first >> second >> wei;
        --first;
        --second;
        array[first][second] = wei;
    }

    for (long long k = 0; k < n; ++k) {
        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; j < n; ++j) {
                array[i][j] = min(array[i][j], array[i][k] + array[k][j]);
            }
        }
    }

    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            cout << array[i][j] << '\t';
        }
        cout << '\n';
    }

    return 0;
}