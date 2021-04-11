#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const long long N = 30001;
vector <pair<long long, long long>> graph[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("pathbgep.in", "r", stdin);
    freopen("pathbgep.out", "w", stdout);

    long long n, m;
    cin >> n >> m;

    long long dist[n];
    long long first, second, wei;

    for (long long i = 0; i < n; ++i) {
        dist[i] = LONG_LONG_MAX;
    }

    for (long long i = 0; i < m; ++i) {
        cin >> first >> second >> wei;
        --first;
        --second;
        graph[first].emplace_back(second, wei);
        graph[second].emplace_back(first, wei);
    }

    dist[0] = 0;
    priority_queue <pair<long long, long long>> q;
    q.push({0, 0});
    while (!q.empty()) {
        long long v = q.top().second;
        long long cur = -q.top().first;
        q.pop();

        if (cur > dist[v])
            continue;

        for (auto j : graph[v]) {
            if (dist[v] + j.second < dist[j.first]) {
                dist [j.first] = dist[v] + j.second;
                q.push({-dist[j.first], j.first});
            }
        }
    }

    for (long long i = 0; i < n; ++i)
        cout << dist[i] << '\t';

    return 0;
}