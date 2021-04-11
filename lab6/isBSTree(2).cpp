#include <iostream>
#include <vector>
using namespace std;

struct tree {
    int key;
    int left;
    int right;
};

void correct(vector <tree> &array, int root,vector <int> &arr) {
    if (root != -1) {
        correct(array, array[root].left, arr);
        arr.push_back(array[root].key);
        correct(array, array[root].right, arr);
    }
}

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, left, right ;
    cin >> n;
    if (n == 0) {
        cout << "YES";
        return 0;
    }
    vector <tree> array(n);
    vector <int> arr;
    for (int i = 0; i < n; ++i) {
        cin >> array[i].key >> left >> right;
        --left;
        --right;
        array[i].left = left;
        array[i].right = right;
    }
    correct(array, 0, arr);
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] >= arr[i]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}