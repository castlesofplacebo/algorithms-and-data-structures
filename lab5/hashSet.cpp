#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
//hash = abs(x) mod m
//m = 1 013
const int m = 9973;

struct list {
    int key;
    list *next;
    list *prev;
};

list *head[m];
list *tail[m];

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
    ad->next = p;
    p->key = k;
    p->prev = ad;
    p->next = nullptr;
    return p;
}

int getHash(int number) {
    return abs(number) % m;
}

void pop(list *ad) {
    int i = getHash(ad->key);
    if ((ad->prev == nullptr) && (ad->next == nullptr)) {
        delete(ad);
        head[i] = nullptr;
        tail[i] = nullptr;
    }
    else if ((ad->prev == nullptr) && (ad->next != nullptr)) {
        ad->next->prev = nullptr;
        head[i] =  ad->next;
        delete(ad);
    }
    else if ((ad->prev != nullptr) && (ad->next == nullptr)) {
        ad->prev->next = nullptr;
        tail[i] = ad->prev;
        delete(ad);
    }
    else if ((ad->prev != nullptr) && (ad->next != nullptr)) {
        ad->prev->next = ad->next;
        ad->next->prev = ad->prev;
        delete(ad);
    }
}

void insertHash(int number) {
    list *current;
    int i = getHash(number);
    if (head[i] == nullptr) {
        head[i] = create(number);
        tail[i] = head[i];
    }
    else {
        current = head[i];
        while ((current->key != number) && (current->next != nullptr)) {
            current = current->next;
        }
        if (current->key == number)
            return;
        else tail[i] = push(tail[i], number);
    }
}

void deleteHash(int number) {
    list *current;
    int i = getHash(number);
    current = head[i];
    if (current == nullptr)
        return;
    while ((current->key != number) && (current->next != nullptr)) {
        current = current->next;
    }
    if (current->key == number)
        pop(current);
    else return;
}

string existsHash(int number) {
    list *current;
    int i = getHash(number);
    current = head[i];
    if (current == nullptr) {
        return "false";
    }
    while ((current->key != number) && (current->next != nullptr)) {
        current = current->next;
    }
    if (current->key == number)
        return "true";
    else return "false";
}

int main() {
    ios_base::sync_with_stdio(0);
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    int number;
    string str;
    for (int i = 0; i < m; ++i) {
        head[i] = nullptr;
        tail[i] = nullptr;
    }
    while (cin >> str) {
        cin >> number;
        if (str == "insert")
            insertHash(number);
        else if (str == "delete")
            deleteHash(number);
        else if (str == "exists")
            cout << existsHash(number) << '\n';
    }
    return 0;
}