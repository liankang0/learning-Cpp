 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-26 11:17:54
 ///
 
#include "MutexLock_Conditon.h"

#include <iostream>
using std::cout;
using std::endl;


int ticket = 200;
bool flag = true;
MutexLock gmutex;
Condition gcondition(gmutex);

//wd::MutexLock gmutex2(gmutex);//error 该语句不能让他编译通过
//把复制构造函数放在私有区

void * windows1(void * arg)
{
	int cnt = 20;
	while(cnt--) {
		//使用MutexLockGuard对象，可以保证不会发生死锁
		MutexLockGuard autolock(gmutex);//RAII
		while(!flag) {//flag == false 使用while是为了防止出现虚假唤醒
			gcondition.wait();//出现异常(虚假)唤醒, 当cond_signal()异常时唤醒所有线程
		}

		//当flag为true时，卖票
		--ticket;
		cout << ">> windows1 " << pthread_self() 
			 << " : left ticket = " << ticket << endl;
		if(flag)
			flag = false;
		gcondition.notify();

		//....return
	}

	return NULL;
}
 
void * windows2(void * arg)
{
	int cnt = 20;
	while(cnt--) {
		MutexLockGuard autolock(gmutex);
		while(flag) {
			gcondition.wait();
		}

		//当flag为false时， 卖票
		--ticket;
		cout << ">> windows2 " << pthread_self() 
			 << " : left ticket = " << ticket << endl;
		if(!flag)
			flag = true;
		gcondition.notify();
	}
	return NULL;
}

int main(void)
{
	pthread_t pthid1, pthid2;
	pthread_create(&pthid1, NULL, windows1, NULL);
	pthread_create(&pthid2, NULL, windows2, NULL);

	pthread_join(pthid1, NULL);
	pthread_join(pthid2, NULL);
	

	return 0;
}
