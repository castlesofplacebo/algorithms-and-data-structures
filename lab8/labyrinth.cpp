#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int number = 101;
int table[number][number];
bool visited [number][number];
pair <int, int> way [number][number];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    pair <int, int> start;
    pair <int, int> end;
    char ch;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            visited[i][j] = false;
            cin >> ch;
            if (ch == '.')
                table[i][j] = 1;
            if (ch == '#')
                table[i][j] = 0;
            if (ch == 'S') {
                table[i][j] = 1;
                start = {i, j};
            }
            if (ch == 'T') {
                table[i][j] = 1;
                end = {i, j};
            }
        }
    }

    queue <pair<int, int>> Q;
    Q.push(start);
    visited[start.first][start.second] = true;
    way[start.first][start.second] = {-1, -1};
    pair <int, int> current;
    while (!Q.empty()) {
        current = Q.front();
        Q.pop();
        if (current == end)
            break;
        vector <pair<int, int>> coord {
                {0,1}, {1,0}, {0, -1}, {-1, 0}
        };
        for (auto i : coord) {
            int x = current.first + i.first;
            int y = current.second + i.second;
            if (!visited[x][y] && table[x][y] && x >= 0 && x < n && y >= 0 && y < m) {
                Q.push({x, y});
                visited[x][y] = true;
                way[x][y] = {current.first, current. second};
            }
        }
    }

    vector <pair<int, int>> path;
    string str{};
    path.push_back(end);
    while (end.first != -1 && end.second != -1) {
        end = way[end.first][end.second];
        path.push_back(end);
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); ++i) {
        current = {path[i].first - 1, path[i].second};
        if (current == path[i + 1])
            str += 'U';
        current = {path[i].first + 1, path[i].second};
        if (current == path[i + 1])
            str += 'D';
        current = {path[i].first, path[i].second - 1};
        if (current == path[i + 1])
            str += 'L';
        current = {path[i].first, path[i].second + 1};
        if (current == path[i + 1])
            str += 'R';
    }

    if (str.empty()) {
        cout << "-1";
        return 0;
    }

    cout << str.size() << '\n';
    cout << str;
    return 0;
}