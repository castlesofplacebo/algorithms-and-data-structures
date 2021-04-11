#include <iostream>
#include <vector>
using namespace std;

struct node {
    int key;
    node *left;
    node *right;
};

node *exists (int key, node *root) {
    if (root == nullptr)
        return nullptr;
    if (root->key == key)
        return root;
    if (root->key > key)
        return exists(key, root->left);
    else return exists(key, root->right);
}

node *create (node *current, int key) {
    current = new node();
    current->key = key;
    current->left = nullptr;
    current->right = nullptr;
    return current;
}

node *insert (int key, node *root) {
    if (root == nullptr) {
        root = create(root, key);
        return root;
    }
    node *q = root;
    while (q != nullptr) {
        if (q->key < key) {
            if (q->right == nullptr) {
                q->right = create(q->right, key);
                return root;
            }
            q = q->right;
        }
        else if (q->key > key) {
            if (q->left == nullptr) {
                q->left = create(q->left, key);
                return root;
            }
            q = q->left;
        }
        else return root;
    }
    return root;
}

node *Next(int key, node *root) {
    node *current = root; //текущий узел
    node *successor = nullptr;//последний посещенный узел с ключом > key
    while (current != nullptr) {
        if (current->key > key) {
            successor = current;
            current = current->left;
        }
        else current = current->right;
    }
    return successor;
}

node *Prev(int key, node *root) {
    node *current = root; //текущий узел
    node *successor = nullptr;//последний посещенный узел с ключом < key
    while (current != nullptr) {
        if (current->key < key) {
            successor = current;
            current = current->right;
        }
        else current = current->left;
    }
    return successor;
}

node *minim (node *root) {
    if (root->left == nullptr)
        return root;
    return minim(root->left);
}

node *del (int key, node *root) {
    if (root == nullptr)
        return root;
    if (root->key > key)
        root->left = del(key, root->left);
    else if (root->key < key)
        root->right = del(key, root->right);
    else if (root->left != nullptr && root->right != nullptr) {
        root->key = minim(root->right)->key;
        root->right = del(root->key, root->right);
    }
    else if (root->left != nullptr)
        root = root->left;
    else if (root->right != nullptr)
        root = root->right;
    else root = nullptr;
    return root;
}

int main() {
    freopen("bstsimple.in", "r", stdin);
    freopen("bstsimple.out", "w", stdout);
    string str;
    int key;
    node *hi = nullptr;
    while (cin >> str) {
        if (str == "insert") {
            cin >> key;
            hi = insert(key, hi);
        }
        if (str == "delete") {
            cin >> key;
            hi = del(key, hi);
        }
        if (str == "exists") {
            cin >> key;
             if (exists(key, hi) != nullptr)
                 cout << "true\n";
             else cout << "false\n";
        }
        if (str == "next") {
            cin >> key;
            node *cur = Next(key, hi);
             if (cur != nullptr)
                 cout << cur->key << '\n';
             else cout << "none\n";
        }
        if (str == "prev") {
            cin >> key;
            node *cur = Prev(key, hi);
            if (cur != nullptr)
                cout << cur->key << '\n';
            else cout << "none\n";
        }
    }
    return 0;
}