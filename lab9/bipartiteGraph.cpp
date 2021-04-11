#include <iostream>
#include <vector>
using namespace std;

const int s = 100003;
vector <int> graph[s];
int tag[s];
bool idx = false;

int color(int c) {
    if (c == 1)
        return 2;
    return 1;
}

void dfs (int &root, int c) {
    tag[root] = c;

    for (int i : graph[root]) {
        if (tag[i] == 0)
            dfs(i, color(c));
        else if (tag[i] == c) {
            idx = true;
            return;
        }
    }
}



int main() {
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        tag[i] = 0;
    }
    int fir, sec;
    for (int i = 1; i <= m; ++i) {
        cin >> fir >> sec;
        graph[fir].push_back(sec);
        graph[sec].push_back(fir);
    }

    for (int i = 1; i <= n; ++i) {
        if (tag[i] == 0)
            dfs(i, 1);
    }

    if (idx)
        cout << "NO" << '\n';
    else cout << "YES" << '\n';

    return 0;
}