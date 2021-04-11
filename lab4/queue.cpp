#include <iostream>
#include <fstream>
using namespace std;

struct list {
    int key;
    list *next;
};

list *head = nullptr;
list *tail = nullptr;

list *create(int k) {
    list *p;
    p = new list();
    p->key = k;
    p->next = nullptr;
    head = p;
    tail = p;
    return p;
}

list *push(list *ad, int k) {
    list *p;
    p = new list();
    ad->next = p;
    p->key = k;
    p->next = nullptr;
    tail = p;
    return p;
}

list *pop(list *ad) {
    if (head->next == nullptr)
        return nullptr;
    else {
        head = head->next;
        return ad;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    //ifstream cin ("queue.in");
    //ofstream cout ("queue.out");
    int n, k;
    cin >> n;
    char c;
    list *ad = nullptr;
    for (int i = 0; i < n; ++i) {
        cin >> c;
        if (c == '+') {
            cin >> k;
            if (ad == nullptr)
                ad = create(k);
            else ad = push(ad, k);
        }
        else {
            cout << head->key << '\n';
            ad = pop(ad);
        }
    }
    return 0;
}