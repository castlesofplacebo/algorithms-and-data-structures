#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int main() {
    freopen("search1.in", "r", stdin);
    freopen("search1.out", "w", stdout);

    string p, t;
    cin >> p >> t;

    int n = t.length();
    int m = p.length();

    vector <int> substring;
    for (int i = 0; i < n - m + 1; ++i) {
        if (t.substr(i, m) == p)
            substring.push_back(i + 1);
    }

    cout << substring.size() << '\n';

    for (int i : substring)
        cout << i << ' ';

    return 0;
}