#include "myString3.h"
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    String s1("hello world");

    String::iterator it = s1.begin();

//    for (; it != s1.end(); ++it) {
//        cout << *it << " ";
//    }
//    cout << endl;

    // c++ 11 for each，底层通过迭代器遍历
    for(auto i : s1){
        cout << i << " ";
    }
    return 0;
}
