#include <iostream>
#include <vector>
#include <string>
using namespace std;
//hash = abs(x) mod m
//m = 9973
const int m = 9973;

struct list {
    string key;
    string mean;
    list *next;
    list *prev;
};

list *head[m];
list *tail[m];

list *create(string &key, string &mean) {
    list *p;
    p = new list();
    p->key = key;
    p->mean = mean;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

list *push(list *ad, string &key, string &mean) {
    list *p;
    p = new list();
    ad->next = p;
    p->key = key;
    p->mean = mean;
    p->prev = ad;
    p->next = nullptr;
    return p;
}

long long getHash(string &current) {
    long long hash = 0;
    long long pow = 1;
    int p = 31;
    for (char i : current) {
        hash += abs((abs(i - 'a' + 1) * pow) % m);
        pow *= p;
    }
    return hash % m;
}

void pop(list *ad) {
    long long i = getHash(ad->key);
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

void putHash(string &key, string &mean) {
    list *current;
    long long i = getHash(key);
    if (head[i] == nullptr) {
        head[i] = create(key, mean);
        tail[i] = head[i];
    }
    else {
        current = head[i];
        while ((current->key != key) && (current->next != nullptr)) {
            current = current->next;
        }
        if (current->key == key)
            current->mean = mean;
        else tail[i] = push(tail[i], key, mean);
    }
}

void deleteHash(string &key) {
    list *current;
    long long i = getHash(key);
    current = head[i];
    if (current == nullptr)
        return;
    while ((current->key != key) && (current->next != nullptr)) {
        current = current->next;
    }
    if (current->key == key)
        pop(current);
    else return;
}

string getMean(string &key) {
    list *current;
    long long i = getHash(key);
    current = head[i];
    if (current == nullptr) {
        return "none";
    }
    while ((current->key != key) && (current->next != nullptr)) {
        current = current->next;
    }
    if (current->key == key)
        return current->mean;
    else return "none";
}

int main() {
    //ios_base::sync_with_stdio(0);
    //freopen("map.in", "r", stdin);
    //freopen("map.out", "w", stdout);
    string str;
    string key, mean;
    for (int i = 0; i < m; ++i) {
        head[i] = nullptr;
        tail[i] = nullptr;
    }
    while (cin >> str) {
        if (str == "put") {
            cin >> key >> mean;
            putHash(key, mean);
        }
        else if (str == "delete") {
            cin >> key;
            deleteHash(key);
        }
        else if (str == "get") {
            cin >> key;
            cout << getMean(key) << '\n';
        }
    }
    return 0;
}