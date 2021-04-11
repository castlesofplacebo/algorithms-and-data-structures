#include <iostream>
#include <vector>
using namespace std;

struct tree {
    int left;
    int right;
    int hei;
    int balance;
};


void balance (vector <tree> &array, int root) {
    if (root != -1) {
        balance(array, array[root].right);
        balance(array, array[root].left);
        array[root].hei = max(array[array[root].right].hei, array[array[root].left].hei) + 1;
        array[root].balance = array[array[root].right].hei - array[array[root].left].hei;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, key, left, right ;
    cin >> n;
    vector <tree> array(n);
    for (int i = 0; i < n; ++i) {
        cin >> key >> left >> right;
        --left;
        --right;
        array[i].left = left;
        array[i].right = right;
        array[i].hei = 0;
    }
    balance(array, 0);
    for (int i = 0; i < n; ++i) {
        cout << array[i].balance << '\n';
    }
    return 0;
}
