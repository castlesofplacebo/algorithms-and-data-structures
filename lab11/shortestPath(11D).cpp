#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long N = 5001;
const long long inf = 8e18;
vector <long long> graph[N];
bool visit [N];
bool mark[N];

struct edge {
    edge (long long first, long long second, long long wei)
            : first(first)
            , second(second)
            , wei(wei)
    {};

    long long first;
    long long second;
    long long wei;
};

void dfs(long long root) {
    visit[root] = true;
    for (auto i : graph[root]) {
        if (!visit[i])
            dfs(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);

    long long n, m, start;
    cin >> n >> m >> start;

    vector <edge> e;
    vector <long long> dist(n);
    vector <long long> parent(n);
    for (long long i = 0; i < n; ++i) {
        dist[i] = inf;
        parent[i] = -1;
        visit[i] = false;
        mark[i] = false;
    }

    long long first, second, wei;
    for (long long j = 0; j < m; ++j) {
        cin >> first >> second >> wei;
        --first;
        --second;
        e.emplace_back(first, second, wei);
        graph[first].push_back(second);
    }

    dist[start - 1] = 0;
    for (long long i = 0; i < n - 1; ++i) {
        for (auto t : e) {
            if (dist[t.first] < inf && dist[t.second] > dist[t.first] + t.wei){
                    dist[t.second] = max(-inf, dist[t.first] + t.wei);
                    parent[t.second] = t.first;
            }
        }
    }

    for (auto t : e) {
        if (dist[t.first] < inf && dist[t.second] > dist[t.first] + t.wei){
            dist[t.second] = max(-inf, dist[t.first] + t.wei);
            parent[t.second] = t.first;
            mark[t.second] = true;
        }
    }

    for (long long i = 0; i < n; ++i) {
        if (mark[i])
            dfs(i);
    }


    for (long long i = 0; i < n; ++i) {
        if (visit[i])
            cout << '-' << '\n';
        else if (dist[i] == inf)
            cout << '*' << '\n';
        else cout << dist[i] << '\n';
    }

    return 0;
}
