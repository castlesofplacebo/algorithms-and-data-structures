#include <iostream>
#include <vector>
using namespace std;

const int s = 100003;
vector <int> graph[s];
bool visit[s];
int relat[s];

void dfs (int &root, int &count) {
    visit[root] = true;
    relat[root] = count + 1;
    for (int i : graph[root]) {
        if (!visit[i])
            dfs(i, count);
    }
}

int comp (int &n) {
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visit[i]) {
            dfs(i, count);
            ++count;
        }
    }
    return count;
}

int main() {
    freopen("components.in", "r", stdin);
    freopen("components.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        visit[i] = false;
    }
    int fir, sec;
    for (int i = 1; i <= m; ++i) {
        cin >> fir >> sec;
        graph[fir].push_back(sec);
        graph[sec].push_back(fir);
    }
    int k = comp(n);
    cout << k << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << relat[i] << '\t';
    }
    /*for (int i = 1; i <= n; ++i) {
        while (!graph[i].empty()) {
            cout << graph[i].front() << '\t';
            swap(graph[i].front(), graph[i].back());
            graph[i].pop_back();
        }
        cout << '\n';
    }*/
    return 0;
}