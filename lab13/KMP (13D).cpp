#include <iostream>
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
    string p;
    int n;

    cin >> n;
    cin >> p;

    p = p + '!';
    vector <int> pr = prefix(p);
    vector <vector<int>> kmp;
    int len = p.length();
    kmp.assign(len, vector <int> (n));

    for (int i = 0; i < len; ++i) {
        for (char c = 'a'; c < 'a' + n; ++c) {
            int cur = c - 'a';
            if (c != p[i] && i > 0)
                kmp[i][cur] = kmp[pr[i - 1]][cur];
            else
                kmp[i][cur] = i + (c == p[i]);
        }
    }

    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < n; ++j)
            cout << kmp[i][j] << ' ';
        cout << '\n';
    }

    return 0;
}