//
// Created by 86188 on 2023/12/29.
//

// 用 new 和 delete 实现写一个对象池
#include <iostream>

template<typename T>
class Queue {
public:
    Queue() {
        _front = _rear = new QueueItem();
    }

    ~Queue() = default;
    // 入队操作 -> 从队尾入
    void push(const T &val) {
        auto *item = new QueueItem(val);
        _rear->_next = item;
        _rear = item;
    }

    // 出队操作 -> 从队头出
    void pop() {
        if (empty()) {
            return;
        }
        QueueItem *first = _front->_next;
        _front->_next = first->_next;
        // 注意！ 否则 _rear 会丢失
        if (_front->_next == nullptr) {
            _rear = _front;
        }
        delete first;
    }

    [[nodiscard]] bool empty() const {
        return _front == _rear;
    }

    [[nodiscard]] T front() const {
        // 注意这里没有判断 队列是否为空
        return _front->_next->_data;
    }

private:
    // 队列的虚拟节点
    struct QueueItem {
        explicit QueueItem(T data = T()) : _data(data), _next(nullptr) {}
        T _data;
        QueueItem *_next;
    };

    QueueItem *_front;  // 虚拟头节点
    QueueItem *_rear;   // 尾节点
};

int main() {
    Queue<int> que;
    for (int i = 0; i < 3; ++i) {
        que.push(i);
        que.pop();
    }
    std::cout << que.empty() << std::endl;
}