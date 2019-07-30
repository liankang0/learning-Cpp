#include <iostream>
#include <string>
using std::cout;
using std::endl;


class Singleton
{
public: 
    static Singleton * getInstance()
    {
        if(_pInstance == NULL)
        {
            _pInstance = new Singleton();
        }
        return new Singleton();
    }
    
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }

private://构造函数私有化
    Singleton(){ cout << "Singleton()" << endl;}
    ~Singleton(){ cout << "~Singleton()" << endl;}
    static Singleton * _pInstance;

};

Singleton * Singleton::_pInstance = NULL;

//Singleton s3;//error

int main()
{
//    Singleton s1;//error
//    Singleton s2;//error
    Singleton * p1 = Singleton::getInstance();
    Singleton * p2 = Singleton::getInstance();
    Singleton * p3 = Singleton::getInstance();
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p3 = " << p3 << endl;
    Singleton::destroy();
    return 0;
}

