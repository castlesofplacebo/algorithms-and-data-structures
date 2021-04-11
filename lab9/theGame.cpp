#include <iostream>
#include <vector>
using namespace std;

const int s = 100001;
vector <int> graph[s];
bool game[s];
bool visit[s];


void dfs (int &root) {
    visit[root] = true;

    for (auto i : graph[root]) {
        if (!visit[i])
            dfs(i);

        if (!game[root] && !game[i])
            game[root] = true;
    }

    if (graph[root].empty()) {
        game[root] = false;
        return;
    }
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int n, m, start;
    cin >> n >> m >> start;

    for (int i = 1; i <= n; ++i) {
        visit[i] = false;
        game[i] = false;
    }

    int fir, sec;
    for (int i = 1; i <= m; ++i) {
        cin >> fir >> sec;
        graph[fir].push_back(sec);
    }

    dfs(start);

    if (game[start]) {
        cout << "First player wins";
        return 0;
    }
    else
        cout << "Second player wins";

    return 0;
}