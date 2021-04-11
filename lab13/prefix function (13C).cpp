#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

vector <int> prefix (string& s) {
    int n = s.length();
    vector <int> pi(n);

    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;

        pi[i] = j;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);

    string p, t;
    cin >> p;

    vector <int> pr = prefix(p);

    for (int i : pr)
        cout << i << ' ';

    return 0;
}