#include <iostream>
using namespace std;

const int N = 1e6 + 1;
int arr[N];
int aT = 0;
int aH = 0;

void push(int number) {
    arr[aT] = number;
    ++aT;
}
void pop() {
    cout << arr[aH] << '\n';
    ++aH;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    int n, number;
    cin >> n;
    char c;
    for (int i = 0; i < n; ++i) {
        cin >> c;
        if (c == '+') {
            cin >> number;
            push(number);
        }
        else pop();
    }
    return 0;
}