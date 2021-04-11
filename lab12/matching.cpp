#include <iostream>
#include <queue>
using namespace  std;

const int N = 500;
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
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;

    int first, second;

    for (int i = 0; i < (n + m + 2); ++i)
        for (int j = 0; j < (n + m + 2); ++j)
            graph[i][j] = 0;

    for (int i = 0; i < k; ++i) {
        cin >> first >> second;
        graph[first][n + second] = 1;
    }

    for (int i = 1; i < n + 1; ++i) {
        graph[0][i] = 1;
    }

    for (int i = n + 1; i < n + m + 1; ++i) {
        graph[i][n + m + 1] = 1;
    }

    /*for (int i = 0; i < n + m + 2; ++i) {
        for (int j = 0; j < n + m + 2; ++j)
            cout << graph[i][j] << '\t';
        cout << '\n';
    }*/

    int flow = 0;
    while (bfs(0, n + m + 1)) {
        for (int v = n + m + 1; v != 0; v = parent[v]) {
            int u = parent[v];
            graph[v][u] += 1;
            graph[u][v] -= 1;
        }
        flow += 1;
    }

    cout << flow;

    return 0;
}