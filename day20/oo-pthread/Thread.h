/*********************************************************************
 * @Author           : liankang
 * @Email            : 349915905@qq.com
 * @Date             : 2019-08-23 11:29
 * @Filename         : Thread.h
 * @Description      : 
 * ******************************************************************/
#ifndef _Thread_H_
#define _Thread_H_
#include "Noncopyable.h"

#include <pthread.h>

class Thread
:public Noncopyable
{
public:
    Thread()
    :_pthid(0)
    ,_isRuning(false)
    {}

    virtual ~Thread();
    
    void start();
    void join();

    static void* threadFunc(void* );
private:
    virtual void run() = 0;//表示这是纯虚数 = 0

private:
    pthread_t _pthid;
    bool _isRuning;
};



#endif

