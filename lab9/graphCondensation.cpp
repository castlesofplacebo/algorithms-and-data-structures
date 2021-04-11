#include <iostream>
#include <vector>
using namespace std;

const int s = 20001;
vector <int> graph[s];
vector <int> trGraph[s];
vector <int> order;
int comp[s];
bool visit[s];

void dfs (int &root) {
    visit[root] = true;
    for (int i : graph[root]) {
        if (!visit[i])
            dfs(i);
    }
    order.push_back(root);
}

void trDfs (int &root, int idx) {
    visit[root] = true;
    comp[root] = idx;
    for (int i : trGraph[root]) {
        if (!visit[i])
            trDfs(i, idx);
    }
}


int main() {
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        visit[i] = false;
    }

    int fir, sec;
    for (int i = 1; i <= m; ++i) {
        cin >> fir >> sec;
        graph[fir].push_back(sec);
        trGraph[sec].push_back(fir);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visit[i])
            dfs(i);
    }

    for (int i = 1; i <= n; ++i) {
        visit[i] = false;
    }

    int idx = 0;
    for (int i = 1; i <= n; ++i) {
        int t = order[n - i];
        if (!visit[t]) {
            ++idx;
            trDfs(t, idx);
        }
    }

    cout << idx << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << comp[i] << '\t';
    }

    return 0;
}