#include <iostream>
#include <vector>
#include <queue>
using namespace  std;

const int MAX = 10001;
const int N = 101;
int parent[N];
bool visit[N];
int graph[N][N];

bool bfs(int s, int t) {
    for (int i = 0; i < t + 1; ++i)
        visit[i] = false;

    queue <int> Q;
    Q.push(s);
    visit[s] = true;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (int v = 0; v < t + 1; ++v) {
            if (!visit[v] && graph[u][v] != 0) {
                visit[v] = true;
                Q.push(v);
                parent[v] = u;
            }
        }
    }

    return visit[t];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    int first, second, capacity;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            graph[i][j] = 0;

    for (int i = 0; i < m; ++i) {
        cin >> first >> second >> capacity;
        --first;
        --second;
        graph[first][second] = capacity;
    }

    int flow = 0;
    while (bfs(0, n - 1)) {
        int df = MAX;

        for (int v = n - 1; v != 0; v = parent[v]) {
            int u = parent[v];
            df = min(df, graph[u][v]);
        }

        for (int v = n - 1; v != 0; v = parent[v]) {
            int u = parent[v];
            graph[v][u] += df;
            graph[u][v] -= df;
        }

        flow += df;
    }

    cout << flow;

    return 0;
}
