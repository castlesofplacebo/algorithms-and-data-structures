#include <iostream>
#include <string>
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

bool is_number(char c) {
    return (c >= 48) && (c <= 57);
}

int main() {
    freopen("postfix.in", "r", stdin);
    freopen("postfix.out", "w", stdout);
    string str;
    list *ad = nullptr;
    getline(cin, str);
    for (auto c : str) {
        if (c == ' ')
            continue;
        if (is_number(c)) {
            if (ad == nullptr)
                ad = create(c - '0');
            else ad = push(ad, c - '0');
            continue;
        }
        else {
            int x = ad->key;
            ad = pop(ad);
            int y = ad->key;
            ad = pop(ad);
            if (c == '+') {
                ad = push(ad, x + y);
                continue;
            }
            else if (c == '-') {
                ad = push(ad, y - x);
                continue;
            }
            else if (c == '*') {
                ad = push(ad, x * y);
                continue;
            }
        }
    }
    cout << ad->key;
    return 0;
}