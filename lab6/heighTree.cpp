#include <iostream>
#include <vector>
using namespace std;

struct tree {
    int left;
    int right;
};

int height(vector <tree> &array, int root) {
    int h = 1;
    if (array[root].left != -1)
        h = max(h, height(array, array[root].left) + 1);
    if (array[root].right != -1)
        h = max(h, height(array,array[root].right ) + 1);
    return h;
}

int main() {
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, key, left, right ;
    cin >> n;
    if (n == 0) {
        cout << '0';
        return 0;
    }
    vector <tree> array(n);
    for (int i = 0; i < n; ++i) {
        cin >> key >> left >> right;
        --left;
        --right;
        array[i].left = left;
        array[i].right = right;
    }
    cout << height(array, 0);
    return 0;
}