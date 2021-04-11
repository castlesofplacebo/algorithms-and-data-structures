#include <iostream>
using namespace std;

const int N = 1e6 + 1;
int arr[N];
int aTop = 0;

void push(int number) {
    ++aTop;
    arr[aTop] = number;
}
void pop() {
    --aTop;
    cout << arr[aTop + 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);
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