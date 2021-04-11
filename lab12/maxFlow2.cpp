#include <iostream>
#include <vector>
#include <queue>

using namespace  std;

struct edge {
    edge(int first, int second, int flow, int capacity)
    : first(first)
    , second(second)
    , flow(flow)
    , capacity(capacity)
    {}

    int first;
    int second;
    int flow;
    int capacity;
};
const int MAX = 1e6;
vector <edge> e;
vector <vector<int>> graph;
vector <int> leveL;
vector <int> rounD;

bool bfs (int n, int s, int t) {
    leveL.assign(n, -1);
    queue <int> Q;

    Q.push(s);
    leveL[s] = 0;

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();

        for (auto& cur : graph[v]) {
            if (e[cur].capacity > e[cur].flow && leveL[e[cur].second] == -1) {
                leveL[e[cur].second] = leveL[v] + 1;
                Q.push(e[cur].second);
            }
        }
    }
    return leveL[t] != -1;
}

int dfs (int v, int flowIn, int t) {
    if (flowIn == 0)
        return 0;

    if (v == t)
        return flowIn;

    for (int& count = rounD[v]; count < graph[v].size(); ++count) {
        int id = graph[v][count];
        int u = e[id].second;

        if (leveL[v] + 1 == leveL[u]) {
            int push = dfs(u, min(flowIn, e[id].capacity - e[id].flow), t);
            if (push != 0) {
                e[id].flow += push;
                e[id ^ 1].flow -= push;
                return push;
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

    graph.resize(n);
    leveL.resize(n);
    rounD.resize(n);

    int first, second, capacity;

    for (int i = 0; i < m; ++i) {
        cin >> first >> second >> capacity;
        --first;
        --second;
        graph[first].push_back(e.size());
        e.emplace_back(first, second, 0, capacity);
        graph[second].push_back(e.size());
        e.emplace_back(second, first, 0, 0);
    }

    int s = 0;
    int t = n - 1;
    int maxflow = 0;
    while (bfs(n, s, t)) {
        rounD.assign(n, 0);

        while (int curFlow = dfs(s, MAX, t))
            maxflow += curFlow;
    }
    cout << maxflow;

    return 0;
}