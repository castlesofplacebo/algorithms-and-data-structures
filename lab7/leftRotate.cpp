#include <iostream>
#include <vector>
using namespace std;

struct node {
    int key;
    int height;
    node *left;
    node *right;

    int curHeight (node *p) {
        return p ? p->height : 0;
    }

    node (int k, node *l, node *r) {
        key = k;
        left = l;
        right = r;
        height = max(curHeight(l), curHeight(r)) + 1;
    }
};

int array[200001][3];
node *root = nullptr;

void createBTS(int n) {
    vector <node*> cur(n);
    for (int i = n - 1; i >= 0; --i)
        cur[i] = new node(array[i][0], (array[i][1] != -1 ? cur[array[i][1]] : nullptr), (array[i][2] != -1 ? cur[array[i][2]] : nullptr));
    root = (n ? cur[0] : nullptr);
}

void fixHeight(node *p) {
    int hl = p->curHeight(p->left);
    int hr = p->curHeight(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node *rotateright(node *p) {
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

node *rotateleft(node *q) {
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

int bfactor (node *p) {
    return p->curHeight(p->right) - p->curHeight(p->left);
}

node *balance (node *p) {
    fixHeight(p);
    if (bfactor(p->right) <  0)
        p->right = rotateright(p->right);
    return rotateleft(p);
}

int idx = 1;
void correctOrder (node *p, int i) {
    array[i][0] = p->key;
    if (p->left != nullptr) {
        ++idx;
        array[i][1] = idx;
        correctOrder(p->left, idx - 1);
    }
    else
        array[i][1] = 0;
    if (p->right != nullptr) {
        ++idx;
        array[i][2] = idx;
        correctOrder(p->right, idx - 1);
    }
    else
        array[i][2] = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("rotation.in", "r", stdin);
    freopen("rotation.out", "w", stdout);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, left, right ;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> array[i][0] >> left >> right;
        array[i][1] = left - 1;
        array[i][2] = right - 1;
    }
    createBTS(n);
    root = balance(root);
    correctOrder(root, 0);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        cout << array[i][0] << '\t' << array[i][1] << '\t' << array[i][2] << '\n';
    }
    return 0;
}
