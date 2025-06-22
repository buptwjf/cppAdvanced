#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

int main() {
    array<int, 5> ar1 = {1, 7, 5, 3, 2};
    auto i = find(ar1.begin(), ar1.end(), 5);
    cout << *i << endl;
    sort(ar1.begin(), ar1.end());

    for (auto a : ar1) { cout << a;}
    cout << endl;
    return 0;
}