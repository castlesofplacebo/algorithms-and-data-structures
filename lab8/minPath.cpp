#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int s = 30007;
vector <int> graph[s];
bool visit[s];
int dist[s];

int main() {
    freopen("pathbge1.in", "r", stdin);
    freopen("pathbge1.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        visit[i] = false;
        dist[i] = -1;
    }

    int fir, sec;
    for (int i = 1; i <= m; ++i) {
        cin >> fir >> sec;
        graph[fir].push_back(sec);
        graph[sec].push_back(fir);
    }

    queue <int> Q;
    Q.push(1);
    visit[1] = true;
    dist[1] = 0;

    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();

        for (int nei : graph[current]) {
            if (!visit[nei]) {
                Q.push(nei);
                visit[nei] = true;
                dist[nei] = dist[current] + 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (dist[i] != -1)
            cout << dist[i] << '\t';
        else cout << "0" << '\t';
    }
    
    return 0;
}