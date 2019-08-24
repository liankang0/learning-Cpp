/*********************************************************************
 * @Author           : liankang
 * @Email            : 349915905@qq.com
 * @Date             : 2019-08-23 11:38
 * @Filename         : Thread.cc
 * @Description      : 
 * ******************************************************************/
#include "Thread.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

Thread::~Thread()
{
    if(_isRuning)
    {
        pthread_detach(_pthid);
    }
}

void Thread::join()
{
    if(_isRuning)
    {
        pthread_join(_pthid, nullptr);
        _isRuning = false;
    }
}

void* Thread::threadFunc(void* arg)
{
    Thread* pthread = static_cast<Thread*>(arg);
    if(pthread)
    {
        pthread->run();
    }
    return nullptr;
}