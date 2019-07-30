#include <iostream>
using std::cout;
using std::endl;


//MutexLock类
class MutexLock
{
public:
    MutexLock()
        :_isLocking(false)
    {
        pthread_mutex_init(&_mutex, NULL);
    }
    ~MutexLock()
    {
        pthread_mutex_destroy(&_mutex);
    }
    void lock();
    void unlock();
    bool isLocking();
    pthread_mutex_t* getMutexPtr();
private:
    pthread_mutex_t _mutex;
    bool _isLocking;
};

void MutexLock::lock()
{
    pthread_mutex_lock(&_mutex);
    _isLocking = true;
}

void MutexLock::unlock()
{
    pthread_mutex_unlock(&_mutex);
    _isLocking = false;
}

bool MutexLock::isLocking() 
{
    return _isLocking;
}

pthread_mutex_t* MutexLock::getMutexPtr()
{
    return &_mutex;
}

//MutexGuard类
class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock & mutex)
    :_mutex(mutex)
    {
        _mutex.lock();
    }
    
    ~MutexLockGuard()
    {
        _mutex.unlock();
    }

private:
    MutexLock & _mutex;
};

// Condition类
class Condition
{
public:
    Condition(MutexLock& mutex)
        :_mutex(mutex)
    {
        pthread_cond_init(&_cond, NULL);
    }
    ~Condition()
    {
        pthread_cond_destroy(&_cond);
    }
    void wait();
    void notify();
    void notifyall();

private:
    pthread_cond_t _cond;
    MutexLock& _mutex;
};

void Condition::wait()
{
    pthread_cond_wait(&_cond, _mutex.getMutexPtr());
}

void Condition::notify()
{ 
    pthread_cond_signal(&_cond);
}

void Condition::notifyall()
{
    pthread_cond_broadcast(&_cond);
}


