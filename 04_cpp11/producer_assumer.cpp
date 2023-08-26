//
// Created by 86188 on 2023/8/25.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <queue> // C++ STL ���е������������̰߳�ȫ��
#include <condition_variable>

using namespace std;

/*
 * C++���̱߳�̵�����
 * 1. �̼߳�Ļ���
 *      ���̴߳��������е�ʱ�򣬴��ھ�̬���������̳߳������н��Ӧ����һ����
 *      ��̬���� => �ٽ�������� => ԭ�Ӳ��� => �̻߳����� mutex ������������ʵ�� CAS
 *      strace ./a.out mutex => pthread_mutex_t
 * 2. �̼߳��ͬ��ͨ��
 *      ������-�������߳�ģ��
 * */

mutex mtx;
condition_variable cv; // �����������������̼߳��ͨ��

class Queue {
public:
    void put(int val) {
        // ʹ�� lock_guard
//        lock_guard<mutex> lck(mtx); // ���� scoped_ptr
        unique_lock<mutex> lck(mtx); // ���� unique_ptr
        while (!que.empty()) {
            // que ��Ϊ�գ�Ӧ��֪ͨ����������������ȥ����
            // 1. �������߳̽���ȴ�״̬��2.���Ұ� mtx �������ͷŵ�
            cv.wait(lck);
        }
        que.push(val);

        /*
         * notify_one
         * notify_all
         * */
        // ֪ͨ�����̣߳���������һ����Ʒ�����ǸϽ����Ѱ�
        // �����̵߳õ���֪ͨ���ͻ�ӵȴ�״̬ => ����״̬ => ��ȡ���������ܼ�������
        cv.notify_all();
        cout << "producer No." << val << " product." << endl;
    }

    int get() {
        unique_lock<mutex> lck(mtx);
        while (que.empty()) {
            // �������̷߳��� que �ǿյģ�֪ͨ�������߳���������Ʒ
            // #1 ����ȴ�״̬ # �ѻ����� mutex �ͷ�
            cv.wait(lck);
        }
        int val = que.front();
        que.pop();
        cv.notify_all(); // ֪ͨ�������̣߳������������
        cout << "consumer No." << val << " product." << endl;
        return val;
    }

private:
    queue<int> que;
};

void producer(Queue *que) {
    for (int i = 0; i < 10; ++i) {
        que->put(i);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

}

void consumer(Queue *que) {
    for (int i = 0; i < 10; ++i) {
        que->get();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    Queue que;
    thread t1(producer, &que);
    thread t2(consumer, &que);
    t1.join();
    t2.join();
    return 0;
}