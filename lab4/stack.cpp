#include <iostream>
#include <fstream>
using namespace std;

struct list {
    int key;
    list *next;
    list *prev;
};

list *create(int k) {
    list *p;
    p = new list();
    p->key = k;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

list *push(list *ad, int k) {
    list *p;
    p = new list();
    p->key = k;
    p->prev = ad;
    p->next = nullptr;
    return p;
}

list *pop(list *ad) {
    list *p = ad;
    if ((ad->next == nullptr) && (ad->prev == nullptr))
        return ad;
    else {
        p->key = ad->prev->key;
        p->next = nullptr;
        p->prev = ad->prev->prev;
        return p;
    }
}

int main() {
    ifstream cin ("stack.in");
    ofstream cout ("stack.out");
    int n, k;
    cin >> n;
    char c;
    list *ad = nullptr;
    for (int i = 0; i < n; ++i) {
        cin >> c;
        if (c == '+') {
            cin >> k;
            if (i == 0)
                ad = create(k);
            else ad = push(ad, k);
        }
        else {
            cout << ad->key << '\n';
            ad = pop(ad);
        }
    }
    cin.close ();
    cout.close ();
    return 0;
}