#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
//hash = abs(x) mod m
//m = 9973
const int m = 9973;

struct list {
    string key;
    int sz = 0;
    vector <string> array;
    list *next{};
    list *prev{};
};

list *head[m];
list *tail[m];

list *create(string &key, string &mean) {
    list *p;
    p = new list();
    p->key = key;
    p->sz++;
    p->array.push_back(mean);
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

list *push(list *ad, string &key, string &mean) {
    list *p;
    p = new list();
    ad->next = p;
    p->sz++;
    p->key = key;
    p->array.push_back(mean);
    p->prev = ad;
    p->next = nullptr;
    return p;
}

long long getHash(string &current) {
    long long hash = 0;
    long long pow = 1;
    int p = 31;
    for (char i : current) {
        hash += abs(abs(i - 'a' + 1) * pow) % m;
        //hash += (i - 'a' + 1) * pow;
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
        while (current != nullptr) {
            if (current->key == key) {
                for (int t = 0; t < current->array.size(); ++t) {
                    if (current->array[t] == mean)
                        return;
                }
                current->array.push_back(mean);
                current->sz++;
                return;
            }
            current = current->next;
        }
        tail[i] = push(tail[i], key, mean);
    }
}

void deleteHash(string &key, string &mean) {
    list *current;
    long long i = getHash(key);
    current = head[i];
    if (current == nullptr)
        return;
    while (current != nullptr) {
        if (current->key == key) {
            for (int t = 0; t < current->array.size(); ++t) {
                if (current->array[t] == mean) {
                    swap(current->array[t], current->array[current->array.size() - 1]);
                    current->array[current->array.size() - 1] = ' ';
                    current->sz--;
                    if (current->sz == 0)
                        pop(current);
                    return;
                }
            }
        }
        current = current->next;
    }
}

void deleteAllHash(string &key) {
    list *current;
    long long i = getHash(key);
    current = head[i];
    //if (current == nullptr)
    //return;
    while (current != nullptr) {
        if (current->key == key) {
            pop(current);
            return;
        }
        current = current->next;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
    cin.tie(nullptr);
    cout.tie(nullptr);
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
            cin >> key >> mean;
            deleteHash(key, mean);
        }
        else if (str == "deleteall") {
            cin >> key;
            deleteAllHash(key);
        }
        else if (str == "get") {
            cin >> key;
            list *current;
            long long i = getHash(key);
            current = head[i];
            if (current == nullptr)
                cout << '0' << '\n';
            else while (current != nullptr) {
                if (current->key == key) {
                    cout << current->sz;
                    for (const auto & t : current->array) {
                        if (!t.empty())
                            cout << '\t' << t;
                    }
                    cout << '\n';
                    continue;
                }
                current = current->next;
            }
            cout << '0' << '\n';
        }
    }
    return 0;
}
/*#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
//hash = abs(x) mod m
//m = 9973

const int m = 9973;
int numb = 0;
string array[537];

struct list {
    string key;
    string mean;
    list *next{};
    list *prev{};
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
        hash += abs((abs(i - 'a' + 1) * pow) % m) % m;
        //hash += (i - 'a' + 1) * pow;
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
        while (current != nullptr) {
            if ((current->key == key) && (current->mean == mean))
                return;
            current = current->next;
        }
        tail[i] = push(tail[i], key, mean);
    }
}

void deleteHash(string &key, string &mean) {
    list *current;
    long long i = getHash(key);
    current = head[i];
    if (current == nullptr)
        return;
    while (current != nullptr) {
        if ((current->key == key) && (current->mean == mean)) {
            pop(current);
            return;
        }
        current = current->next;
    }
}

void deleteAllHash(string &key) {
    list *current;
    long long i = getHash(key);
    current = head[i];
    //if (current == nullptr)
        //return;
    while (current != nullptr) {
        if (current->key == key)
            pop(current);
        current = current->next;
    }
}

void getMean(string &key) {
    int temp = 0;
    list *current;
    long long i = getHash(key);
    current = head[i];
    if (current == nullptr) {
        return;
    }
    while (current != nullptr) {
        if (current->key == key) {
            array[temp] = current->mean;
            ++temp;
            ++numb;
        }
        current = current->next;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    //freopen("multimap.in", "r", stdin);
    //freopen("multimap.out", "w", stdout);
    ifstream cin ("multimap.in");
    ofstream cout ("multimap.out");
    cin.tie(nullptr);
    cout.tie(nullptr);
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
            cin >> key >> mean;
            deleteHash(key, mean);
        }
        else if (str == "deleteall") {
            cin >> key;
            deleteAllHash(key);
        }
        else if (str == "get") {
            cin >> key;
            getMean(key);
            cout << numb;
            if (numb == 0) {
                cout << '\n';
                continue;
            }
            for (int i = 0; i < numb; ++i) {
                cout << '\t' << array[i];
            }
            cout << '\n';
            numb = 0;
        }
    }
    cin.close ();
    cout.close ();
    return 0;
}*/