#include <iostream>
#include <vector>
using namespace std;


struct set {
    int count = 0;
    int m = 550;
    vector<string> arr[550];

    set () {
        for (auto & i : arr) {
            i = {};
        }
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

    bool exists (string &mean) {
        long long i = getHash(mean);
        for (auto t : arr[i])
            if (t == mean)
                return true;
        return false;
    }

    void put (string &mean) {
        long long i = getHash(mean);
        if (exists(mean))
            return;
        ++count;
        arr[i].push_back(mean);
    }

    void Delete (string &mean) {
        if (!exists(mean))
            return;
        --count;
        int idx = 0;
        long long i = getHash(mean);
        for (int t = 0 ; t < arr[i].size(); ++t) {
            if (arr[i][t] == mean)
                idx = t;
        }
        swap(arr[i][idx], arr[i][arr[i].size() - 1]);
        arr[i].pop_back();
    }

    void print() {
        cout << count;
        for (int t = 0; t < 550; ++t) {
            for (auto j : arr[t])
                cout << '\t' << j;
        }
        cout << '\n';
    }
};

struct map {
    int m = 1e6 + 2;
    //long long m = 1e6 + 22;
    vector <pair<string, set*>> array[(long long) (1e6 + 2)];

    map () {
        for (int i = 0; i < 1000002; ++i) {
            array[i] = {};
        }
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

    bool exists(string &key) {
        long long i = getHash(key);
        for (int t = 0; t < array[i].size(); ++t) {
            if (array[i][t].first == key)
                return true;
        }
        return false;
    }

    void putHash (string &key, string &mean) {
        long long i = getHash(key);
        if (!exists(key)) {
            array[i].push_back({key, new set});
            array[i].back().second->put(mean);
            return;
        }
        for (int t = 0; t < array[i].size(); ++t) {
            if (array[i][t].first == key)
                array[i][t].second->put(mean);
        }
    }

    void deleteHash(string &key, string &mean) {
        int idx = -1;
        if (!exists(key))
            return;
        int i = getHash(key);
        for (int t = 0; t < array[i].size(); ++t) {
            if (array[i][t].first == key) {
                idx = t;
            }
        }
        if (idx == -1)
            return;
        array[i][idx].second->Delete(mean);
        if (array[i][idx].second->count == 0)
            deleteAllHash(key);
    }

    void deleteAllHash(string &key) {
        int idx = -1;
        if (!exists(key))
            return;
        int i = getHash(key);
        for (int t = 0; t < array[i].size(); ++t) {
            if (array[i][t].first == key) {
                idx = t;
            }
        }
        if (idx == -1)
            return;
        if (array[i].empty())
            return;
        swap(array[i][idx], array[i][array[i].size() - 1]);
        array[i].pop_back();
    }

    void getMean(string &key) {
        if (!exists(key)) {
            cout << "0\n";
            return;
        }
        long long i = getHash(key);
        for (int t = 0; t < array[i].size(); ++t) {
            if (array[i][t].first == key) {
                array[i][t].second->print();
                //return;
            }
        }
    }

};

int main() {
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
    cin.tie(NULL);
    cout.tie(NULL);
    string str;
    string key, mean;
    map *Map = new map();
    while (cin >> str) {
        if (str == "put") {
            cin >> key >> mean;
            Map->putHash(key, mean);
        }
        else if (str == "delete") {
            cin >> key >> mean;
            Map->deleteHash(key, mean);
        }
        else if (str == "deleteall") {
            cin >> key;
            Map->deleteAllHash(key);
        }
        else if (str == "get") {
            cin >> key;
            Map->getMean(key);
        }
    }
    return 0;
}