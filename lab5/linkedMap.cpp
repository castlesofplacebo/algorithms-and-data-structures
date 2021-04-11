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
    list *next{};
    list *prev{};
    list *nextMap{};//next in associative array
    list *prevMap{};//prev in associative array
};

list *head[m];
list *tail[m];
list *help = nullptr;//последний добавленный элемент

list *create(string &key, string &mean) {
    list *p;
    p = new list();
    p->key = key;
    p->mean = mean;
    p->nextMap = nullptr;
    p->prevMap = nullptr;
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
    p->nextMap = nullptr;
    p->prevMap = nullptr;
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
    if ((ad->prevMap != nullptr) && (ad->nextMap != nullptr)) {
        ad->prevMap->nextMap = ad->nextMap;
        ad->nextMap->prevMap = ad->prevMap;
    }
    else if ((ad->prevMap == nullptr) && (ad->nextMap != nullptr)) {
        ad->nextMap->prevMap = nullptr;
    }
    else if ((ad->prevMap != nullptr) && (ad->nextMap == nullptr)) {
        ad->prevMap->nextMap = nullptr;
        help = ad->prevMap;
    }
    else help = nullptr;

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
    //if (help != nullptr)
    //cout << help << '\t' << help->key << '\t' << help->prevMap << '\t' << help->nextMap << '\n';
    list *current;
    long long i = getHash(key);
    if (head[i] == nullptr) {
        head[i] = create(key, mean);
        if (help != nullptr) { //если эл-т не первый - переносим ссылку из передыдущего(help) на текущий (head[i])
            help->nextMap = head[i];
        }
        head[i]->prevMap = help;
        tail[i] = head[i];
        help = head[i];
    }
    else {
        current = head[i];
        while ((current->key != key) && (current->next != nullptr)) {
            current = current->next;
        }
        if (current->key == key)
            current->mean = mean;
        else  {
            tail[i] = push(tail[i], key, mean);
            help->nextMap = tail[i];
            tail[i]->prevMap = help;
            help = tail[i];
        }
    }
    //cout << help << '\t' << help->key << '\t' << help->prevMap << '\t' << help->nextMap << '\n';
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

string prevMean(string &key) {
    list *current;
    long long i = getHash(key);
    current = head[i];
    if (current == nullptr) {
        return "none";
    }
    while ((current->key != key) && (current->next != nullptr)) {
        current = current->next;
    }
    if (current->key == key) {
        if (current->prevMap == nullptr)
            return "none";
        else return current->prevMap->mean;
    }
    else return "none";
}

string nextMean(string &key) {
    list *current;
    long long i = getHash(key);
    current = head[i];
    if (current == nullptr) {
        return "none";
    }
    while ((current->key != key) && (current->next != nullptr)) {
        current = current->next;
    }
    if (current->key == key) {
        if (current->nextMap == nullptr)
            return "none";
        else return current->nextMap->mean;
    }
    else return "none";
}

int main() {
    ios_base::sync_with_stdio(0);
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);
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
        } else if (str == "delete") {
            cin >> key;
            deleteHash(key);
        } else if (str == "get") {
            cin >> key;
            cout << getMean(key) << '\n';
        } else if (str == "prev") {
            cin >> key;
            cout << prevMean(key) << '\n';
        }
        else if (str == "next") {
            cin >> key;
            cout << nextMean(key) << '\n';
        }
        /*else if (str == "array") {
            for (auto & i : head) {
                if (i != nullptr)
                    cout << i << '\t' << i->key << '\t' << i->prevMap << '\t' << i->nextMap << '\n';
            }
        }*/
    }
    return 0;
}