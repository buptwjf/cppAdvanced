//
// Created by 86188 on 2023/8/17.
//

/*
 * 1. C++ STL中的绑定器
 *      bind1st : operator() 的第一个形参变量绑定成一个确定的值
 *      bind2nd : operator() 的第二个形参变量绑定成一个确定的值
 * 2. C++ 11 从 Boost库中引入 bind 绑定器和 function 函数对象机制
 *
 * 3. lambda 表达式，底层依赖函数对象的机制实现的
*/
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

template<typename Container>
void showContainer(Container &con) {
    // 这里需要加个 typename，否则会报错
//    typename Container::iterator it = con.begin();
    auto it = con.begin();  // 用 auto 更好
    for (; it != con.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1); // 0 ~ 100
    }

    showContainer(vec);
    sort(vec.begin(), vec.end());  // 默认小到大排序
    showContainer(vec);

    // greater 是一个二元函数对象 或者叫 二元 谓词
    sort(vec.begin(), vec.end(), greater<int>());

    showContainer(vec);

    // 把 70 按顺序插入到 vec 容器中 找到第一个小于 70 的数字
    // 方法 1：需要一个 一元 谓词
    struct smaller70 {
        bool operator()(const int &a) {
            return a < 70;
        }
    };
//    auto loc = find_if(vec.begin(), vec.end(), smaller70());
//    vec.insert(loc, 70);
//    showContainer(vec);

    // 方法 2：使用绑定器
    /*
     * greater a > b
     * less    a < b
     * 绑定器 + 二元函数对象 => 一元函数对象
     * bind1st + greater bool operator() (70, const _Ty& _Right)
     * bind2nd + less bool operator() (const _Ty& _left, 70)
     * */
    auto loc1 = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 70));
//    auto loc1 = find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 70)); 也可以
    if(loc1!= vec.end());
    vec.insert(loc1, 70);
    showContainer(vec);
    return 0;
}