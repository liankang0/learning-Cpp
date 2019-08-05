#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#include <iostream>

using std::cout;
using std::endl;

template <class T>
class Singleton
{
public:

    //多线程不安全
    //template <typename...Args>
    // static T* getInstance(Args... args)
    // {
    //     if(NULL == _pInstance)
    //     {
    //     ::atexit(destory);
    //     _pInstance = new T(args...);
    //     }
    //     return _pInstance;
    // }

    static void destory()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }

    //多线程安全
    template <typename...Args>
    static T* getInstance(Args... args)
    {
        if(NULL == _pInstance)
        {
        pthread_once(&_once, init);
        *_pInstance = T(args...);
        }
        return _pInstance;
    }

    static void init()
    {
        _pInstance = new T();
        ::atexit(destory);
    }

private:
    Singleton()
    {
        cout << "Singleton()" << endl;
    }

    ~Singleton()
    {
        cout << "Singleton()" << endl;
    }

private:
    static T* _pInstance;
    static pthread_once_t _once;
};

template <class T>
T * Singleton<T>::_pInstance = nullptr;//懒汉模式

template <class T>
pthread_once_t Singleton<T>::_once = PTHREAD_ONCE_INIT;


class Point 
{
public:
    Point()
    :_ix(0)
    ,_iy(0)
    {}
    Point(int ix, int iy)
    :_ix(ix)
    ,_iy(iy)
    {}
private:
    int _ix;
    int _iy;
};



int main(void)
{
    Point* p3 = Singleton<Point>::getInstance();
    Point* p4 = Singleton<Point>::getInstance();
    printf("%p\n", p3);
    printf("%p\n", p4);

    return 0;
}
