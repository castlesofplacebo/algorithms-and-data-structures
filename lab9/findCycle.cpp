#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int s = 100003;
vector <int> graph[s];
char cyColor[s];
int cyPath[s];
int cyStart;
int cyEnd;


bool dfs (int &root) {
    cyColor[root] = 1;
    for (int i : graph[root]) {
        if (cyColor[i] == 0) {
            cyPath[i] = root;
            if (dfs(i))
                return true;
        }
        else if (cyColor[i] == 1) {
            cyEnd = root;
            cyStart = i;
            return true;
        }
    }
    cyColor[root] = 2;
    return false;
}


int main() {
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cyColor[i] = 0;
        cyPath[i] = -1;
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
        cout << "NO";
        return 0;
    }
    else {
        cout << "YES" << '\n';
        vector <int> path;
        path.push_back(cyStart);
        for (int i = cyEnd; i != cyStart; i = cyPath[i]) {
            path.push_back(i);
        }
        reverse(path.begin(), path.end());
        for (int i : path) {
            cout << i << '\t';
        }

    }

    return 0;
}