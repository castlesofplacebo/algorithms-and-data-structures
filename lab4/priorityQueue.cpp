#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector <pair<int,int>> heap;
int array[1000001];

void siftUp (int i) {
    if (i <= 1)
        return;
    if (heap[i / 2].second > heap[i].second) {
        array[heap[i].first] = i / 2;
        array[heap[i / 2].first] = i;
        swap(heap[i], heap[i / 2]);
        siftUp(i / 2);
    }
}

void siftDown(int i) {
    int largest;
    int l = 2*i;
    int r =  2*i + 1;
    if ((l < heap.size()) && (heap[l].second < heap[i].second)) {
        largest = l;
    }
    else largest = i;
    if ((r < heap.size()) && (heap[r].second < heap[largest].second)) {
        largest = r;
    }
    if (largest != i) {
        array[heap[i].first] = largest;
        array[heap[largest].first] = i;
        swap(heap[i], heap[largest]);
        siftDown(largest);
    }
}

void push (int number, int i) {
    array[i] = heap.size();
    heap.emplace_back(i, number);
    siftUp(heap.size() - 1);
}

void extractMin() {
    if (heap.size() <= 1) {
        cout << '*' << '\n';
        return;
    }
    cout << heap[1].second << '\n';
    array[heap[1].first] = heap.size() - 1;
    array[heap[heap.size() - 1].first] = 1;
    swap(heap[1], heap[heap.size() - 1]);
    heap.pop_back();
    siftDown(1);
}

void decrease(int x, int y) {
    heap[array[x]].second = y;
    siftUp(array[x]);
}

int main() {
    //ifstream cin ("priorityqueue.in");
    //ofstream cout ("priorityqueue.out");
    string str;
    int i = 0;
    int number;
    int x,y;
    heap.emplace_back(0,0);
    while (cin >> str) {
        ++i;
        if (str == "push") {
            cin >> number;
            push(number, i);
        }
        if (str == "extract-min")
            extractMin();
        if (str == "decrease-key") {
            cin >> x >> y;
            decrease(x, y);
        }
    }
    //cin.close ();
    //cout.close ();
    return 0;
}