#include <iostream>
#include <vector>
using namespace std;

const long long inf = 8e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);

    long long n, start, finish;
    cin >> n >> start >> finish;

    vector <vector<pair<long long, long long>>> graph(n);
    bool visit[n];
    long long dist[n];

    long long wei;
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            cin >> wei;
            if (wei != -1)
                graph[i].emplace_back(j, wei);
        }
        visit[i] = false;
        dist[i] = inf;
    }

    dist[start - 1] = 0;
    for (long long i = 0; i < n; ++i) {
        long long v = -1;
        for (long long j = 0; j < n; ++j)
            if (!visit[j] && (v == -1 || dist[j] < dist[v]))
                v = j;
        if (dist[v] == inf)
            break;
        visit[v] = true;

        for (auto j : graph[v]) {
            long long to = j.first;
            long long len = j.second;
            if (dist[v] + len < dist[to]) {
                dist [to] = dist[v] + len;
            }
        }
    }

    if (dist[finish - 1] != inf)
        cout << dist[finish - 1];
    else cout << "-1";

    return 0;
}