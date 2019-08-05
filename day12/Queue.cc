#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template <class T, int kSize = 10>
class Queue
{
public:
    Queue()
    :_head(0)
    ,_tail(0)
    ,_data(new T[kSize]())
    {   cout << "Queue()" << endl; }
    ~Queue()
    {
        delete [] _data;
    }
    void push(const T& t);
    void pop();
    T& front();
    T& back();
    bool empty();
    bool full();
private:
    T* _data;
    int _head;
    int _tail;
};

template <class T, int kSize>
bool Queue<T, kSize>::empty()
{
    return _tail == _head;
}

template <class T, int kSize>
bool Queue<T, kSize>::full()
{
    return _tail == (_head + 1) % kSize;
}

template <class T, int kSize>
void Queue<T, kSize>::push(const T& t)
{
    if(!full())
    {
        _data[_head++] = t;
        _head %= kSize;
    }
    else
    {
        cout << "队列满，入队失败" << endl;
    }
}

template <class T, int kSize>
T& Queue<T, kSize>::front()
{
    return _data[_head];
}

template <class T, int kSize>
T& Queue<T, kSize>::back()
{
    return _data[_tail];
}

template <class T, int kSize>
void Queue<T, kSize>::pop()
{
    if(!empty())
    {
        ++_tail;
        _tail %= kSize;
    }
    else
    {
        cout << "队列为空，不能抛出" << endl;
    }

}

void test1()
{
    Queue<string> queue;
    cout << "此时队列是否为空？" << queue.empty() << endl;
    queue.push("aaa");
    cout << "此时队列是否为空？" << queue.empty() << endl;

    for(int idx = 1; idx != 11; ++idx)
    {
        queue.push(string(3, 'a' + idx));
    }
    cout << "此时队列是否已满？" << queue.full() << endl;
    while(!queue.empty())
    {
        cout << queue.back() << endl;
        queue.pop();
    }
    cout << "此时队列是否为空？" << queue.empty() << endl;
}




int main(void)
{
    test1();
    return 0;
}