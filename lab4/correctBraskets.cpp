#include <iostream>
#include <fstream>
using namespace std;

struct list {
    char key;
    list *next;
    list *prev;
};

list *create(char k) {
    list *p;
    p = new list();
    p->key = k;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

list *push(list *ad, char k) {
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
        return nullptr;
    else {
        p->key = ad->prev->key;
        p->next = nullptr;
        p->prev = ad->prev->prev;
        return p;
    }
}

bool empty(list *ad) {
    return ad == nullptr;
}

string correct (string &str) {
    list *ad = nullptr;
    for (auto c : str) {
        if ((c == '(') || (c == '[')) {
            if (ad == nullptr)
                ad = create(c);
            else ad = push(ad, c);
        }
        else {
            if (empty(ad))
                return "NO";
            if (((ad->key == '[') && (c != ']')) || ((ad->key == '(') && (c != ')'))) {
                return "NO";
            }
            ad = pop(ad);
        }
    }
    if (empty(ad))
        return "YES";
    else return "NO";
}

int main() {
    ifstream cin ("brackets.in");
    ofstream cout ("brackets.out");
    string str;
    while (cin >> str) {
        cout << correct(str) << '\n';
    }
    cin.close ();
    cout.close ();
    return 0;
}