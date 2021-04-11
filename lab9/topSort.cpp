#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int s = 100003;
vector <int> graph[s];
vector <int> tsort;
bool visit[s];
char cyColor[s];
int cyStart;

bool dfs (int &root) {
    cyColor[root] = 1;
    for (int i : graph[root]) {
        if (cyColor[i] == 0) {
            if (dfs(i))
                return true;
        }
        else if (cyColor[i] == 1) {
            cyStart = 10;
            return true;
        }
    }
    cyColor[root] = 2;
    return false;
}

void topDfs(int &root) {
    visit[root] = true;
    for (int i : graph[root]) {
        if (!visit[i])
            topDfs(i);
    }
    tsort.push_back(root);
}

void topsort (int &n) {
    for (int i = 1; i <= n; ++i) {
        if (!visit[i])
            topDfs(i);
    }
    reverse(tsort.begin(), tsort.end());
}

int main() {
    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cyColor[i] = 0;
        visit[i] = false;
    }

    int fir, sec;
    for (int i = 1; i <= m; ++i) {
        cin >> fir >> sec;
        graph[fir].push_back(sec);
    }

    cyStart = -1;
    for (int i = 1; i <= n; ++i)
        if (dfs(i))
            break;

    if (cyStart == -1) {
        topsort(n);
        for (int i : tsort) {
            cout << i << '\t';
        }
    }
    else {
        cout << "-1" << '\n';
        return 0;
    }

    return 0;
}