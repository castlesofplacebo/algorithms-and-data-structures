#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long none = 1e9;
const long long inf = 8e18;

struct edge {
    edge (long long first, long long second, long long wei)
    : first(first)
    , second(second)
    , wei(wei)
    {};

    long long first;
    long long second;
    long long wei;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);

    long long n, cur;
    cin >> n;

    vector <edge> e;
    vector <long long> dist(n);
    vector <long long> parent(n);
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            cin >> cur;
            if (cur != none)
                e.emplace_back(i, j, cur);
        }
        dist[i] = 0;
        parent[i] = -1;
    }

    long long x = -1;
    for (long long i = 0; i < n; ++i) {
        x = -1;
        for (auto t : e) {
            if (dist[t.second] > dist[t.first] + t.wei) {
                dist[t.second] = max(-inf, dist[t.first] + t.wei);
                parent[t.second] = t.first;
                x = t.second;
            }
        }
    }

    if (x == -1) {
        cout << "NO";
        return 0;
    }

   long long y = x;
    for (long long i = 0; i < n; ++i) {
        y = parent[y];
    }
 
    vector <long long> path;
    x = y;
    do {
        path.push_back(x);
        x = parent[x];
    } while (x != y);

    path.push_back(x);
    reverse(path.begin(), path.end());

    cout << "YES" << '\n';
    cout << path.size() << '\n';
    for (auto i : path)
        cout << i + 1 << '\t';

    return 0;
}
