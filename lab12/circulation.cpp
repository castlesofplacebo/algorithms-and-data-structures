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
    freopen("circulation.in", "r", stdin);
    freopen("circulation.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    n = n + 2;
    graph.resize(n);
    leveL.resize(n);
    rounD.resize(n);
    vector <int> minCapacity(m);

    int first, second, minCap, maxCap;
    int s = 0;
    int t = n - 1;

    for (int i = 0; i < m; ++i) {
        cin >> first >> second >> minCap >> maxCap;
        minCapacity[i] = minCap;

        graph[s].push_back(e.size());
        e.emplace_back(s, second, 0, minCap);
        graph[second].push_back(e.size());
        e.emplace_back(second, s, 0, 0);

        graph[first].push_back(e.size());
        e.emplace_back(first, second, 0, maxCap - minCap);
        graph[second].push_back(e.size());
        e.emplace_back(second, first, 0, 0);

        graph[first].push_back(e.size());
        e.emplace_back(first, t, 0, minCap);
        graph[t].push_back(e.size());
        e.emplace_back(t, first, 0, 0);
    }

    while (bfs(n, s, t)) {
        rounD.assign(n, 0);
        while (dfs(s, MAX, t));
    }

    for (auto cur : graph[0]) {
        if (e[cur].flow < e[cur].capacity) {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES" << '\n';
    int count = 2;
    for (int i = 0; i < m; ++i) {
        cout << e[count].flow + minCapacity[i] << '\n';
        count += 6;
    }

    return 0;
}