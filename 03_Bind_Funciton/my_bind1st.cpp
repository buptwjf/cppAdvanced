//
// Created by 86188 on 2023/8/17.
//

/*
 *  自己实现 bind1st 和 bind2nd
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

// 实现 my_find_if
template<typename Iterator, typename Compare>
Iterator my_find_if(Iterator first, Iterator last, Compare comp) {
    for (Iterator it = first; it != last; ++it) {
        if (comp(*it)) {
            return it;
        }
    }
    return last;
}


// 实现 bind1st => 将二元函数对象转化为一元函数对象
template<typename Compare, typename T>
class _mybind1st {
public:
    _mybind1st(Compare comp, T val) : _comp(comp), _val(val) {}

    bool operator()(const T &second) {
        return _comp(_val, second); // 底层实际调用的还是 greater
    }

private:
    Compare _comp;
    T _val;
};

// 用函数模板封装 一元函数对象的产生
template<typename Compare, typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T &val) {
    // 直接使用函数模板的好处：可以进行类型的实参推演
    return _mybind1st<Compare, T>(comp, val);
};


// 实现 bind2nd => 将二元函数对象转化为一元函数对象
template<typename Compare, typename T>
class _mybind2nd {
public:
    _mybind2nd(Compare comp, T val) : _comp(comp), _val(val) {}

    bool operator()(const T &first) {
        return _comp(first, _val); // 底层实际调用的还是 greater
    }

private:
    Compare _comp;
    T _val;
};

// 用函数模板封装 一元函数对象的产生
template<typename Compare, typename T>
_mybind2nd<Compare, T> mybind2nd(Compare comp, const T &val) {
    // 直接使用函数模板的好处：可以进行类型的实参推演
    return _mybind2nd<Compare, T>(comp, val);
};

int main() {
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 20; ++i) {
        vec.push_back(rand() % 100 + 1); // 0 ~ 100
    }

    showContainer(vec);
    // greater 是一个二元函数对象 或者叫 二元 谓词
    // 从大到小排序
    sort(vec.begin(), vec.end(), greater<int>());
    showContainer(vec);
    // 使用自己的绑定器
//    auto loc1 = my_find_if(vec.begin(), vec.end(), _mybind1st(greater<int>(), 70));
    auto loc1 = my_find_if(vec.begin(), vec.end(), mybind2nd(less<int>(), 70));
    if (loc1 != vec.end());
    vec.insert(loc1, 70);
    showContainer(vec);
    return 0;
}