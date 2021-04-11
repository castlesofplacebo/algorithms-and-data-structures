#include <iostream>
#include <vector>
using namespace std;

const int s = 101;
vector <int> graph[s];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    int fir, sec;
    for (int i = 1; i <= m; ++i) {
        cin >> fir >> sec;
        graph[fir].push_back(sec);
        graph[sec].push_back(fir);
    }

    for (int i = 1; i <= n; ++i) {
        cout << graph[i].size() << '\t';
    }

    return 0;
}