#include <iostream>
#include <vector>
#include <cmath>
using namespace  std;

struct point {
    int x;
    int y;
};

int distance (point &a, point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);

    int n;
    cin >> n; //n <=5000
    vector <point> p(n);
    vector <bool> visited(n);
    vector<int> Min(n, INT32_MAX);
    int dist[n][n];

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        cin >> p[i].x >> p[i].y; //-10 000 <= x, y <= 10 000
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            dist[i][j] = distance(p[i], p[j]);
        }

    Min[0] = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j)
            if (!visited[j] && (v == -1 || Min[j] < Min[v]))
                v = j;

        visited[v] = true;

        for (int to = 0; to < n; ++to)
            if (!visited[to] && dist[v][to] < Min[to] && v != to) {
                Min[to] = dist[v][to];
            }
    }

    double ans = 0.0;
    for (int i : Min) {
        ans = ans + sqrt(i);
    }

    cout.precision(10);
    cout << ans;
    return 0;
}