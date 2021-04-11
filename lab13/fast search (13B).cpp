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
    freopen("search2.in", "r", stdin);
    freopen("search2.out", "w", stdout);

    string p, t;
    cin >> p >> t;
    //p - substring t - string
    int n = p.length();
    int m = t.length();

    string pPlusT = p + '!' + t;
    vector <int> pr = prefix(pPlusT);
    vector <int> substring;

    for (int i = 0; i < m; ++i) {
        if (pr[i + n + 1] == n)
            substring.push_back(i - n + 2);
    }

    cout << substring.size() << '\n';

    for (int i : substring)
        cout << i << ' ';

    return 0;
}