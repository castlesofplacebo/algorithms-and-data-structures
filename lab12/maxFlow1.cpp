#include <iostream>
#include <vector>
#include <queue>
using namespace  std;

const int MAX = 10001;
const int N = 101;
vector<int> graph[N];
int capacity[N][N];

int bfs(int s, int t, vector <int>& parent) {
    for (int i = 0; i < t + 1; ++i)
        parent[i] = -1;

    queue <pair<int, int>> Q;
    Q.push({s, MAX});
    parent[s] = -2;

    while (!Q.empty()) {
        int u = Q.front().first;
        int minFlow = Q.front().second;
        Q.pop();

        for (int v = 0; v < t + 1; ++v) {
            if (parent[v] == -1 && capacity[u][v] != 0) {
                parent[v] = u;
                int newFlow = min(minFlow, capacity[u][v]);
                if (v == t)
                    return newFlow;
                Q.push({v, newFlow});
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    int first, second, wei;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            capacity[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i) {
        cin >> first >> second >> wei;
        --first;
        --second;
        graph[first].push_back(second);
        capacity[first][second] = max(wei, capacity[first][second]);
    }

    /*for (int i = 0; i < n; ++i) {
        cout << i << '\t';
        for (int j : graph[i])
            cout << j << '\t';
        cout << '\n';
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << capacity[i][j] << '\t';
        cout << '\n';
    }*/

    int flow = 0;
    vector <int> parent(n);

    int cur;
    while (cur = bfs(0, n - 1, parent)) {
        flow += cur;
        for (int v = n - 1; v != 0; v = parent[v]) {
            int u = parent[v];
            capacity[v][u] += cur;
            capacity[u][v] -= cur;
        }
    }

    cout << flow;

    return 0;
}