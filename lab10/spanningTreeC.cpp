#include <iostream>
#include <vector>
#include <queue>
using namespace  std;

int main() {
    //freopen("spantree3.in", "r", stdin);
    //freopen("spantree3.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    vector <pair<int, int>> graph[n];
    bool visited[n];

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    int fir, sec, wei;
    for (int i = 0; i < m; ++i) {
        cin >> fir >> sec >> wei;
        --fir;
        --sec;
        graph[fir].emplace_back(sec, wei);
        graph[sec].emplace_back(fir, wei);
    }

    long long ans = 0;
    priority_queue <pair<long long, long long>, vector<pair<long long, long long>>, greater<>> q;
    q.push({0, 0});

    while (!q.empty()) {
        pair<long long, long long> cur = q.top();
        q.pop();

        long long dst = cur.first;
        long long v = cur.second;

        if (visited[v]) {
            continue;
        }

        visited[v] = true;
        ans += dst;

        for (pair<long long, long long> e: graph[v]) {
            long long u = e.first;
            long long curLen = e.second;

            if (!visited[u]) {
                q.push({curLen, u});
            }
        }
    }

    cout << ans;

    return 0;
}