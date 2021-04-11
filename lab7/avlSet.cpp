#include <iostream>
#include <vector>
using namespace std;

struct node {
    int key;
    int height;
    node *left;
    node *right;

    node (int k) {
        key = k;
        height = 1;
        left = right = nullptr;
    }

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
    if (bfactor(p) == 2) {
        if (bfactor(p->right) <  0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
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

node *insert (node *p, int key) {
    if (!p)
        return new node(key);
    if (p->key > key)
        p->left = insert(p->left, key);
    else if (p->key < key)
        p->right = insert(p->right, key);
    return balance(p);
}

node *findMin(node *p) {
    return p->right ? findMin(p->right) : p;
}

node *removeMin(node *p) {
    if (!p)
        return nullptr;
    if (p->right == nullptr)
        return p->left;
    p->right = removeMin(p->right);
    return balance(p);
}

node *del(node *p, int key) {
    if (!p)
        return nullptr;
    if (p->key > key)
        p->left = del(p->left, key);
    else if (p->key < key)
        p->right = del(p->right, key);
    else {
        node *q = p->left;
        node *r = p->right;
        delete(p);
        if (!q)
            return r;
        node *min = findMin(q);
        min->left = removeMin(q);
        min->right = r;
        return balance(min);
    }
    return balance(p);
}

bool exists(node *p, int key) {
    if (!p)
        return false;
    if (p->key > key)
       exists(p->left, key);
    else if (p->key < key)
        exists(p->right, key);
    else return p->key == key;
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("avlset.in", "r", stdin);
    freopen("avlset.out", "w", stdout);
    cin.tie(nullptr);
    cout.tie(nullptr);
    char ch;
    int n, num;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> ch >> num;
        if (ch == 'A') {
            root = insert(root, num);
            if (root != nullptr)
                cout << bfactor(root) << '\n';
            else  cout << '0' << '\n';
        }
        if (ch == 'D') {
            root = del(root, num);
            if (root != nullptr)
                cout << bfactor(root) << '\n';
            else  cout << '0' << '\n';
        }
        if (ch == 'C') {
            if (exists(root, num))
                cout << 'Y' << '\n';
            else cout << 'N' << '\n';
        }
    }
    return 0;
}
