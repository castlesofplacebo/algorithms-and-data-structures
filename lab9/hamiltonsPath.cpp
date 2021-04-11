#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int s = 100001;
vector <int> graph[s];
vector <int> order;
bool visit[s];

void dfs (int &root) {
    visit[root] = true;
    for (int i : graph[root]) {
        if (!visit[i])
            dfs(i);
    }
    order.push_back(root);
}

bool isPath(int prev, int cur) {
    for (auto i : graph[prev]) {
        if (i == cur)
            return true;
    }
    return false;
}

int main() {
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        visit[i] = false;
    }

    int fir, sec;
    for (int i = 1; i <= m; ++i) {
        cin >> fir >> sec;
        --fir;
        --sec;
        graph[fir].push_back(sec);
    }

    for (int i = 0; i < n; ++i) {
        if (!visit[i])
            dfs(i);
    }

    reverse(order.begin(), order.end());

    for (int i = 1; i < n; ++i) {
        if (!isPath(order[i - 1], order[i])) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";

    return 0;
}