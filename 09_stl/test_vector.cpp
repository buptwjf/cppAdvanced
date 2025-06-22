#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> v;
    cout << sizeof (v) << endl;   // 3 * 8
    cout << v.capacity() << endl;
    v.push_back(1);
    cout << sizeof (v) << endl;
    cout << v.capacity() << endl; // 1
    v.push_back(2);
    cout << v.capacity() << endl; // 2 = 1*2
    v.push_back(3);
    cout << v.capacity() << endl; // 4 = 2*2

    //
    auto i =  find(v.begin(), v.end(), 2);
    cout << *i <<endl;
}