#include <iostream>
#include <vector>
using namespace std;

struct tree {
    int key;
    int left;
    int right;
};

bool correct(vector <tree> &array, int i, int min, int max) {
    if (i == -1)
        return true;

    if (array[i].key <= min || array[i].key >= max)
        return false;

    return (correct(array, array[i].left, min, array[i].key) && correct(array, array[i].right, array[i].key, max));
}

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);

    int n, l, r;
    cin >> n;

    if (n == 0) {
        cout << "YES";
        return 0;
    }
    vector <tree> array(n);
    for (int i = 0; i < n; ++i) {
        cin >> array[i].key >> l >> r;
        array[i].left = l - 1;
        array[i].right = r - 1;
    }

    if (correct(array, 0, INT_MIN, INT_MAX))
        cout << "YES";
    else
        cout << "NO";

    return 0;
}